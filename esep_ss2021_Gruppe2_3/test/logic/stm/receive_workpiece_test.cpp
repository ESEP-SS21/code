#include <gtest/gtest.h>
#include <logic/stm/StmRecieveWrpc/sub_belt_states.h>

#include "logic/stm/StmRecieveWrpc/recieve_wrpc_context.h"
#include "util/stm_test_client.h"

#include "util/stm_test_base.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::receiveWrpcStm;

INIT_STM_TEST(testReceiveWrpcStm, ReceiveWrpcContext, ::logic::datamodel::UnitType::PRIMARY)


TEST_F(testReceiveWrpcStm, BeginsInRightState){
    ASSERT_STATE(BeltNotRunning);
}

TEST_F(testReceiveWrpcStm, Transition) {
    data._operating_mode = ::logic::datamodel::OperatingMode::RUNNING;
    test_transition_to<BeltRunning>({EventType::EVNT_SEN_LB_ST_BLCK}, {{EventType::EVNT_ACT_BELT_FWD}});
    test_transition_to<BeltNotRunning>({EventType::EVNT_ACT_BELT_STP}, {EventType::EVNT_ACT_BELT_STP});
}

TEST_F(testReceiveWrpcStm, BlockingIfNotRunning) {
    data._operating_mode = ::logic::datamodel::OperatingMode::ESTOP;
    test_transition_to<BeltNotRunning>({EventType::EVNT_SEN_LB_ST_BLCK}, {});
}

}
}
}
