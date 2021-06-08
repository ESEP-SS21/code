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

INIT_STM_TEST(testSortWrpc, SortWrpcContext, UnitType::PRIMARY)

TEST_F(testSortWrpc, BeginsInRightState) {
    ASSERT_STATE(WaitingForWrpc);
}

TEST_F(testSortWrpc, WrpcFitsInSortingOrder) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc = create_wp_hm();
    data.get_height_switch_sec()->enter_workpiece(wrpc);

    //WaitingForWrpc -> NoDiscard
    test_transition_to<NoDiscard>( { EventType::EVNT_SEN_LB_SW_BLCK }, { {
            EventType::EVNT_ACT_SORT_NO_DSC } });
    //NoDiscard -> WaitingToPass
    test_transition_to<WaitingToPass>( { EventType::EVNT_SEN_LB_SW_CLR },
            { Event::CreateTimer(TimerID::SORT_WRPC_NO_DISCARD_PASS, 500) });
    //WaitingToPass -> WaitingForWrpc
    test_transition_to<WaitingForWrpc>( { EventType::EVNT_TIM_ALRT,
            static_cast<int>(TimerID::SORT_WRPC_NO_DISCARD_PASS) }, {
            { EventType::EVNT_ACT_SORT_RST } });
    ASSERT_EQ(wrpc, data.get_height_switch_sec()->first_workpiece());
    ASSERT_EQ(wrpc, data.get_switch_end_sec()->last_workpiece());
}

TEST_F(testSortWrpc, WrpcStuck) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc = create_wp_l();
    data.get_height_switch_sec()->enter_workpiece(wrpc);

    //WaitingForWrpc -> Discard
    test_transition_to<Discard>( { EventType::EVNT_SEN_LB_SW_BLCK },
            { { EventType::EVNT_ACT_SORT_DSC },
                    { Event::CreateTimer(TimerID::SORT_WRPC_STUCK, 3000) } });
    //Discard -> WrpcStuck
    test_transition_to<WrpcStuck>( { EventType::EVNT_TIM_ALRT,
            static_cast<int>(TimerID::SORT_WRPC_STUCK) }, { { EventType::EVNT_WRN } });
    //WrpcStuck -> WaitingForRampToClear
    test_transition_to<WaitingForRampToClear>( { EventType::EVNT_SEN_LB_SW_CLR }, { {
            EventType::EVNT_WRN_GONE }, { EventType::EVNT_ACT_SORT_RST }, {
            EventType::EVNT_ACT_BELT_STP }, { Event::CreateTimer(TimerID::SORT_WRPC_FULL, 200) } });

    ASSERT_EQ(wrpc, data.get_height_switch_sec()->first_workpiece());
    //ASSERT_EQ(wrpc, data.get_switch_end_sec()->last_workpiece());
}

} /* namespace stm */
} /* namespace logic */
} /* namespace test */

