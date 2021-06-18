#include <gtest/gtest.h>
#include "logic/stm/StmSortWrpc/sort_wrpc_context.h"
#include "util/stm_test_client.h"
#include "util/stm_test_base.h"
#include "../workpiece_helper.h"
#include "logic/stm/StmSortWrpc/states/operating_substates/WaitingForWrpc.h"
#include "logic/stm/StmSortWrpc/states/operating_substates/RampFull.h"
#include "logic/stm/StmSortWrpc/states/operating_substates/WaitingForRampToClear.h"
#include "logic/stm/StmSortWrpc/states/wfstc_substates/NoDiscard.h"
#include "logic/stm/StmSortWrpc/states/wfstc_substates/Discard.h"
#include "logic/stm/StmSortWrpc/states/wfstc_substates/WaitingToPass.h"
#include "logic/stm/StmSortWrpc/states/wfstc_substates/WrpcStuck.h"
#include "logic/stm/StmSortWrpc/states/sub_wfstc.h"
#include "logic/stm/StmSortWrpc/states/sub_operating.h"
#include <iostream>

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::sortWrpcStm;
using namespace ::logic::datamodel;
using namespace ::dispatcher;

INIT_STM_TEST(testSortWrpcPrimary, SortWrpcContext, UnitType::PRIMARY)
INIT_STM_TEST(testSortWrpcSecondary, SortWrpcContext, UnitType::SECONDARY)

TEST_F(testSortWrpcPrimary, BeginsInRightState) {
    ASSERT_STATE(WaitingForWrpc);
}

TEST_F(testSortWrpcPrimary, WrpcFitsInSortingOrder) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc = create_wp_hm();
    data.get_height_switch_sec()->enter_workpiece(wrpc);

    // WaitingForWrpc -> NoDiscard
    test_transition_to<NoDiscard>( { EventType::EVNT_SEN_LB_SW_BLCK }, { {
            EventType::EVNT_ACT_SORT_NO_DSC } });
    // NoDiscard -> WaitingToPass
    test_transition_to<WaitingToPass>( { EventType::EVNT_SEN_LB_SW_CLR },
            { Event::CreateTimer(TimerID::SORT_WRPC_NO_DISCARD_PASS, PASS_TIME_MS) });
    // WaitingToPass -> WaitingForWrpc
    test_transition_to<WaitingForWrpc>( { EventType::EVNT_TIM_ALRT,
            static_cast<int>(TimerID::SORT_WRPC_NO_DISCARD_PASS) }, {
            { EventType::EVNT_ACT_SORT_RST } });
    ASSERT_EQ(0, data.get_height_switch_sec()->workpiece_count());
    ASSERT_EQ(wrpc, data.get_switch_end_sec()->last_workpiece());
    ASSERT_EQ(data.get_next_in_order(), WorkpieceType::WRPC_HB);
}

TEST_F(testSortWrpcPrimary, WrpcDiscardWithStuck) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc = create_wp_l();
    data.get_height_switch_sec()->enter_workpiece(wrpc);

    // WaitingForWrpc -> Discard
    test_transition_to<Discard>( { EventType::EVNT_SEN_LB_SW_BLCK },
            { { EventType::EVNT_ACT_SORT_DSC },
                    { Event::CreateTimer(TimerID::SORT_WRPC_STUCK, SW_CLR_TIME_TOLERANCE_MS) } });
    // Discard -> WrpcStuck
    test_transition_to<WrpcStuck>( { EventType::EVNT_TIM_ALRT,
            static_cast<int>(TimerID::SORT_WRPC_STUCK) }, { { EventType::EVNT_WRN } });
    // WrpcStuck -> WaitingForRampToClear
    test_transition_to<WaitingForRampToClear>( { EventType::EVNT_SEN_LB_SW_CLR }, { {
            EventType::EVNT_WRN_GONE }, { EventType::EVNT_ACT_SORT_RST }, {
            EventType::EVNT_ACT_BELT_STP }, { Event::CreateTimer(TimerID::SORT_WRPC_FULL, RA_CLR_TIME_TOLERANCE_MS) } });
    // WaitingForRampToClear -> WaitingForWrpc
    test_transition_to<WaitingForWrpc>( { EventType::EVNT_SEN_LB_RA_CLR }, { });

    ASSERT_EQ(0, data.get_height_switch_sec()->workpiece_count());
    ASSERT_EQ(0, data.get_switch_end_sec()->workpiece_count());
}

TEST_F(testSortWrpcPrimary, RegularDiscardOfWrpc) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc = create_wp_l();
    data.get_height_switch_sec()->enter_workpiece(wrpc);

    // WaitingForWrpc -> Discard
    test_transition_to<Discard>( { EventType::EVNT_SEN_LB_SW_BLCK },
            { { EventType::EVNT_ACT_SORT_DSC },
                    { Event::CreateTimer(TimerID::SORT_WRPC_STUCK, SW_CLR_TIME_TOLERANCE_MS) } });
    // Discard -> WaitingForRampToClear
    test_transition_to<WaitingForRampToClear>( { EventType::EVNT_SEN_LB_SW_CLR },
            { { EventType::EVNT_ACT_SORT_RST }, { EventType::EVNT_ACT_BELT_STP }, {
                    Event::CreateTimer(TimerID::SORT_WRPC_FULL, RA_CLR_TIME_TOLERANCE_MS) } });
    // WaitingForRampToClear -> WaitingForWrpc
    test_transition_to<WaitingForWrpc>( { EventType::EVNT_SEN_LB_RA_CLR }, { });

    ASSERT_EQ(0, data.get_height_switch_sec()->workpiece_count());
    ASSERT_EQ(0, data.get_switch_end_sec()->workpiece_count());
}

TEST_F(testSortWrpcPrimary, MakeSpaceInRampWhileFullCapacity) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc = create_wp_l();
    data.get_height_switch_sec()->enter_workpiece(wrpc);

    // WaitingForWrpc -> Discard
    test_transition_to<Discard>( { EventType::EVNT_SEN_LB_SW_BLCK },
            { { EventType::EVNT_ACT_SORT_DSC },
                    { Event::CreateTimer(TimerID::SORT_WRPC_STUCK, SW_CLR_TIME_TOLERANCE_MS) } });
    // Discard -> WaitingForRampToClear
    test_transition_to<WaitingForRampToClear>( { EventType::EVNT_SEN_LB_SW_CLR },
            { { EventType::EVNT_ACT_SORT_RST }, { EventType::EVNT_ACT_BELT_STP }, {
                    Event::CreateTimer(TimerID::SORT_WRPC_FULL, RA_CLR_TIME_TOLERANCE_MS) } });
    ASSERT_TRUE(data.belt_empty());

    // WaitingForRampToClear -> RampFull
    test_transition_to<RampFull>( { EventType::EVNT_TIM_ALRT,
            static_cast<int>(TimerID::SORT_WRPC_FULL) }, { { EventType::EVNT_WRN } });
    ASSERT_TRUE(data._ramp_full);
    // RampFull -> WaitingForWrpc
    test_transition_to<WaitingForWrpc>( { EventType::EVNT_SEN_LB_RA_CLR }, { {
            EventType::EVNT_WRN_GONE } });
    ASSERT_FALSE(data._ramp_full);
}

TEST_F(testSortWrpcPrimary, RampFullButWrpcIsInOrder) {
    ASSERT_EQ(data._unit_type, UnitType::PRIMARY);
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc_discard = create_wp_l();
    data.get_height_switch_sec()->enter_workpiece(wrpc_discard);

    // WaitingForWrpc -> Discard
    test_transition_to<Discard>( { EventType::EVNT_SEN_LB_SW_BLCK },
            { { EventType::EVNT_ACT_SORT_DSC },
                    { Event::CreateTimer(TimerID::SORT_WRPC_STUCK, SW_CLR_TIME_TOLERANCE_MS) } });
    // Discard -> WaitingForRampToClear
    test_transition_to<WaitingForRampToClear>( { EventType::EVNT_SEN_LB_SW_CLR },
            { { EventType::EVNT_ACT_SORT_RST }, { EventType::EVNT_ACT_BELT_STP }, {
                    Event::CreateTimer(TimerID::SORT_WRPC_FULL, RA_CLR_TIME_TOLERANCE_MS) } });
    ASSERT_TRUE(data.belt_empty());
    // WaitingForRampToClear -> RampFull
    test_transition_to<RampFull>( { EventType::EVNT_TIM_ALRT,
            static_cast<int>(TimerID::SORT_WRPC_FULL) }, { { EventType::EVNT_WRN } });
    ASSERT_TRUE(data._ramp_full);

    Workpiece wrpc_no_discard = create_wp_hm();
    data.get_height_switch_sec()->enter_workpiece(wrpc_no_discard);

    // RampFull -> NoDiscard
    test_transition_to<NoDiscard>( { EventType::EVNT_SEN_LB_SW_BLCK }, { EventType::EVNT_ACT_SORT_NO_DSC });
    // NoDiscard -> WaitingToPass
    test_transition_to<WaitingToPass>( { EventType::EVNT_SEN_LB_SW_CLR },
            { Event::CreateTimer(TimerID::SORT_WRPC_NO_DISCARD_PASS, PASS_TIME_MS) });

    ASSERT_TRUE(data._ramp_full);
    ASSERT_EQ(0, data.get_height_switch_sec()->workpiece_count());
    ASSERT_EQ(wrpc_no_discard, data.get_switch_end_sec()->last_workpiece());
}

TEST_F(testSortWrpcSecondary, DiscardButRampFullError) {
    ASSERT_EQ(data._unit_type, UnitType::SECONDARY);
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc_discard_1 = create_wp_l();
    data.get_height_switch_sec()->enter_workpiece(wrpc_discard_1);

    // WaitingForWrpc -> Discard
    test_transition_to<Discard>( { EventType::EVNT_SEN_LB_SW_BLCK },
            { { EventType::EVNT_ACT_SORT_DSC },
                    { Event::CreateTimer(TimerID::SORT_WRPC_STUCK, SW_CLR_TIME_TOLERANCE_MS) } });
    // Discard -> WaitingForRampToClear
    test_transition_to<WaitingForRampToClear>( { EventType::EVNT_SEN_LB_SW_CLR },
            { { EventType::EVNT_ACT_SORT_RST }, { EventType::EVNT_ACT_BELT_STP }, {
                    Event::CreateTimer(TimerID::SORT_WRPC_FULL, RA_CLR_TIME_TOLERANCE_MS) } });
    ASSERT_TRUE(data.belt_empty());
    // WaitingForRampToClear -> RampFull
    test_transition_to<RampFull>( { EventType::EVNT_TIM_ALRT,
            static_cast<int>(TimerID::SORT_WRPC_FULL) }, { { EventType::EVNT_WRN } });
    ASSERT_TRUE(data._ramp_full);

    Workpiece wrpc_discard_2 = create_wp_l();
    data.get_height_switch_sec()->enter_workpiece(wrpc_discard_2);

    // RampFull -> RampFull
    Event error_event {EventType::EVNT_ERR, static_cast<int>(::logic::datamodel::Error::RAMP_FULL), true};
    test_transition_to<RampFull>( { EventType::EVNT_SEN_LB_SW_BLCK },
            { {error_event} });
    ASSERT_TRUE(data._ramp_full);

}

} /* namespace stm */
} /* namespace logic */
} /* namespace test */

