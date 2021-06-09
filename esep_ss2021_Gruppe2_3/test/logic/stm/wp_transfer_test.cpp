#include <gtest/gtest.h>
#include "util/stm_test_client.h"
#include "util/stm_test_base.h"
#include "../workpiece_helper.h"
#include "logic/stm/StmWpTransfer/wp_transfer_context.h"
#include "logic/stm/StmWpTransfer/wp_transfer_states.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::StmWpTransfer;
using namespace ::logic::datamodel;

INIT_STM_TEST(testWpTransferPrimary, WpTransferContext, UnitType::PRIMARY)
INIT_STM_TEST(testWpTransferSecondary, WpTransferContext, UnitType::SECONDARY)

TEST_F(testWpTransferPrimary, BeginsInRightState) {
    ASSERT_EQ(data._unit_type, UnitType::PRIMARY);
    ASSERT_STATE(Waiting);
}

TEST_F(testWpTransferSecondary, TransferInSecondary) {
    ASSERT_EQ(data._unit_type, UnitType::SECONDARY);
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc = create_wp_hm();
    wrpc.height_2 = wrpc.height_1;
    wrpc.determine_type();
    data.get_switch_end_sec()->enter_workpiece(wrpc);

    // Waiting -> Waiting
    test_transition_to<Waiting>( { EventType::EVNT_SEN_LB_EN_BLCK }, { });
}

TEST_F(testWpTransferPrimary, RegularTransferWithoutBlockLastRemaining) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc = create_wp_hm();
    data.get_switch_end_sec()->enter_workpiece(wrpc);

    // Waiting -> NotBlocked
    test_transition_to<NotBlocked>( { EventType::EVNT_SEN_LB_EN_BLCK },
            { { EventType::EVNT_WRPC_TRNS_RQ, static_cast<int>(wrpc.encode().code), true }, { Event::CreateTimer(
                    TimerID::WRPC_TRANSFER_BLOCKED, 50, false) } });

    // Waiting -> WaitingForWpToLeave
    test_transition_to<WaitingForWpToLeave>( { EventType::EVNT_ACK, 0, true }, { });

    // WaitingForWpToLeave -> WaitingForFinTransfer
    test_transition_to<WaitingForFinTransfer>( { EventType::EVNT_SEN_LB_EN_CLR }, {
            Event::CreateTimer(TimerID::WRPC_TRANSFER_LAST_REMAINING_WRPC, 500) });
    ASSERT_TRUE(data.get_switch_end_sec()->workpiece_count() == 0);

    // WaitingForFinTransfer -> Waiting
    test_transition_to<Waiting>( { EventType::EVNT_TIM_ALRT,
            static_cast<int>(TimerID::WRPC_TRANSFER_LAST_REMAINING_WRPC) }, { {
            EventType::EVNT_ACT_BELT_STP } });
}

TEST_F(testWpTransferPrimary, RegularTransferWithoutBlockBeltNotEmptyYet) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc_1 = create_wp_hm();
    data.get_switch_end_sec()->enter_workpiece(wrpc_1);

    // Waiting -> NotBlocked
    test_transition_to<NotBlocked>( { EventType::EVNT_SEN_LB_EN_BLCK },
            { { EventType::EVNT_WRPC_TRNS_RQ, static_cast<int>(wrpc_1.encode().code), true }, { Event::CreateTimer(
                    TimerID::WRPC_TRANSFER_BLOCKED, 50, false) } });

    // Waiting -> WaitingForWpToLeave
    test_transition_to<WaitingForWpToLeave>( { EventType::EVNT_ACK, 0, true }, { });

    // WaitingForWpToLeave -> WaitingForFinTransfer
    test_transition_to<WaitingForFinTransfer>( { EventType::EVNT_SEN_LB_EN_CLR }, {
            Event::CreateTimer(TimerID::WRPC_TRANSFER_LAST_REMAINING_WRPC, 500) });
    ASSERT_TRUE(data.get_switch_end_sec()->workpiece_count() == 0);

    Workpiece wrpc_2 = create_wp_l();
    data.get_start_height_sec()->enter_workpiece(wrpc_2);

    // WaitingForFinTransfer -> Waiting
    test_transition_to<Waiting>( { EventType::EVNT_TIM_ALRT,
            static_cast<int>(TimerID::WRPC_TRANSFER_LAST_REMAINING_WRPC) }, { });
}

TEST_F(testWpTransferPrimary, TransferAndBlock) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc = create_wp_hm();
    data.get_switch_end_sec()->enter_workpiece(wrpc);

    // Waiting -> NotBlocked
    test_transition_to<NotBlocked>( { EventType::EVNT_SEN_LB_EN_BLCK },
            { { EventType::EVNT_WRPC_TRNS_RQ, static_cast<int>(wrpc.encode().code), true }, { Event::CreateTimer(
                    TimerID::WRPC_TRANSFER_BLOCKED, 50, false) } });

    // NotBlocked -> Blocked
    test_transition_to<Blocked>( { EventType::EVNT_TIM_ALRT,
            static_cast<int>(TimerID::WRPC_TRANSFER_BLOCKED) },
            { { EventType::EVNT_ACT_BELT_STP } });
    ASSERT_TRUE(data._belt_blocked);

    // Blocked -> WaitingForWpToLeave
    test_transition_to<WaitingForWpToLeave>( { EventType::EVNT_ACK, 0, true }, { {
            EventType::EVNT_ACT_BELT_FWD } });
    ASSERT_FALSE(data._belt_blocked);
}

} /* namespace stm */
} /* namespace logic */
} /* namespace test */
