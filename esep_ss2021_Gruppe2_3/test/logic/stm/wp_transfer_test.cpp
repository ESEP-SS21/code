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

TEST_F(testWpTransferPrimary, RegularTransferWithoutBlock) {
    data._operating_mode = OperatingMode::RUNNING;
    Workpiece wrpc = create_wp_hm();
    data.get_switch_end_sec()->enter_workpiece(wrpc);

    // Waiting -> NotBlocked
    //test_transition_to<NotBlocked>( { EventType::EVNT_SEN_LB_EN_BLCK },
    //        { { Event::CreateTimer(TimerID::WRPC_TRANSFER_BLOCKED, 50, false) }, {
    //                EventType::EVNT_WRPC_TRNS_RQ } });

    // Waiting -> WaitingForWpToLeave
    //test_transition_to<WaitingForWpToLeave>( { EventType::EVNT_ACK },
    //        { { Event::CreateTimer(TimerID::WRPC_TRANSFER_WAIT4EXIT, 2000, false) } });
}

} /* namespace stm */
} /* namespace logic */
} /* namespace test */
