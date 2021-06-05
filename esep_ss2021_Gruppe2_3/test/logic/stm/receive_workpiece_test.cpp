#include <gtest/gtest.h>
#include <logic/stm/StmRecieveWrpc/states/sub_belt_not_running.h>
#include <logic/stm/StmRecieveWrpc/states/sub_belt_running.h>
#include "logic/stm/StmRecieveWrpc/recieve_wrpc_context.h"
#include "util/stm_test_client.h"

#include "util/stm_test_base.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::recieveWrpcStm;

INIT_STM_TEST(testRecieveWrpcStm, RecieveWrpcContext)


TEST_F(testRecieveWrpcStm, BeginsInRightState){
    ASSERT_STATE(BeltNotRunning);
}

TEST_F(testRecieveWrpcStm, Transition) {
    data.set_operating_mode(::logic::datamodel::OperatingMode::RUNNING);
    test_transition_to<BeltRunning>({EventType::EVNT_SEN_LB_ST_BLCK}, {{EventType::EVNT_ACT_BELT_FWD}});
    test_transition_to<BeltNotRunning>({EventType::EVNT_ACT_BELT_STP}, {EventType::EVNT_ACT_BELT_STP});
}

TEST_F(testRecieveWrpcStm, BlockingIfNotRunning) {
    data.set_operating_mode(::logic::datamodel::OperatingMode::ESTOP);
    test_transition_to<BeltNotRunning>({EventType::EVNT_SEN_LB_ST_BLCK}, {});
}

}
}
}
