#include <gtest/gtest.h>
#include <logic/stm/StmRecieveWrpc/receive_wrpc_states.h>

#include "logic/stm/StmRecieveWrpc/recieve_wrpc_context.h"
#include "util/stm_test_client.h"

#include "util/stm_test_base.h"

#include "../workpiece_helper.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::receiveWrpcStm;
using namespace ::logic::datamodel;

INIT_STM_TEST(testReceiveWrpcStmPrimary, ReceiveWrpcContext, ::logic::datamodel::UnitType::PRIMARY)
INIT_STM_TEST(testReceiveWrpcStmSecondary, ReceiveWrpcContext, ::logic::datamodel::UnitType::SECONDARY)


TEST_F(testReceiveWrpcStmPrimary, BeginsInRightState){
    test_start_state<BeltNotRunning>({
        {EventType::EVNT_ACT_BELT_STP}
    });
}

TEST_F(testReceiveWrpcStmPrimary, TransitionPri) {

    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    data._belt_blocked = false;
    test_start_state<BeltNotRunning>({
        {EventType::EVNT_ACT_BELT_STP}
    });
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 0);

    test_transition_to<BeltRunning>({EventType::EVNT_ACT_BELT_FWD}, {EventType::EVNT_ACT_BELT_FWD});
    test_transition_to<BeltRunning>({EventType::EVNT_SEN_LB_ST_BLCK});
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 1);
    test_transition_to<BeltNotRunning>({EventType::EVNT_ACT_BELT_STP}, {EventType::EVNT_ACT_BELT_STP});

}

TEST_F(testReceiveWrpcStmPrimary, TransitionBeltNotBlockedPri) {
    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    data._belt_blocked = false;
    test_start_state<BeltNotRunning>({
        {EventType::EVNT_ACT_BELT_STP}
    });
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 0);
    test_transition_to<BeltRunning>({EventType::EVNT_SEN_LB_ST_BLCK}, {EventType::EVNT_ACT_BELT_FWD});
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 1);

}

TEST_F(testReceiveWrpcStmPrimary, TransitionBeltBlockedPri) {
    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    data._belt_blocked = true;
    test_start_state<BeltNotRunning>({
        {EventType::EVNT_ACT_BELT_STP}
    });
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 0);
    test_transition_to<BeltNotRunning>({EventType::EVNT_SEN_LB_ST_BLCK});
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 1);

}

TEST_F(testReceiveWrpcStmSecondary, TransitionSec) {

    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    data._belt_blocked = false;

    auto wrpc = std::make_shared<Workpiece>(create_wp_hm());
    data.set_pending_transfer(wrpc);

    test_start_state<BeltNotRunning>({
        {EventType::EVNT_ACT_BELT_STP}
    });

    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 0);

    test_transition_to<BeltRunning>({EventType::EVNT_ACT_BELT_FWD}, {EventType::EVNT_ACT_BELT_FWD});
    test_transition_to<BeltRunning>({EventType::EVNT_SEN_LB_ST_BLCK});
    ASSERT_TRUE(data._belt_blocked);
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 1);
    ASSERT_EQ(data.get_start_height_sec()->first_workpiece(), *wrpc);
    test_transition_to<BeltNotRunning>({EventType::EVNT_ACT_BELT_STP}, {EventType::EVNT_ACT_BELT_STP});

}

TEST_F(testReceiveWrpcStmSecondary, TransitionBeltNotBlockedSec) {
    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    data._belt_blocked = false;
    auto wrpc = std::make_shared<Workpiece>(create_wp_hm());
    data.set_pending_transfer(wrpc);

    test_start_state<BeltNotRunning>({
        {EventType::EVNT_ACT_BELT_STP}
    });
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 0);
    test_transition_to<BeltRunning>({EventType::EVNT_SEN_LB_ST_BLCK}, {EventType::EVNT_ACT_BELT_FWD});
    ASSERT_TRUE(data._belt_blocked);
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 1);
    ASSERT_EQ(data.get_start_height_sec()->first_workpiece(), *wrpc);
}

TEST_F(testReceiveWrpcStmSecondary, TransitionBeltBlockedSec) {
    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    data._belt_blocked = true;
    auto wrpc = std::make_shared<Workpiece>(create_wp_hm());
    data.set_pending_transfer(wrpc);
    test_start_state<BeltNotRunning>({
        {EventType::EVNT_ACT_BELT_STP}
    });
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 0);
    test_transition_to<BeltNotRunning>({EventType::EVNT_SEN_LB_ST_BLCK});
    ASSERT_TRUE(data.get_start_height_sec()->workpiece_count() == 1);
    ASSERT_EQ(data.get_start_height_sec()->first_workpiece(), *wrpc);
}

}
}
}
