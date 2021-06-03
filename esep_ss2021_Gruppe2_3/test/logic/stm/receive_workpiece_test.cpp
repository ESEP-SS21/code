#include <gtest/gtest.h>
#include <logic/stm/StmRecieveWrpc/states/sub_belt_not_running.h>
#include <logic/stm/StmRecieveWrpc/states/sub_belt_running.h>
#include <logic/stm/StmRecieveWrpc/states/estop.h>
#include <logic/stm/StmRecieveWrpc/states/idle.h>
#include "logic/stm/StmRecieveWrpc/recieve_wrpc_context.h"
#include "util/stm_test_client.h"

#include "util/stm_test_base.h"

namespace test {
namespace logic {
namespace stm {

using namespace ::logic::stm::top_level;

INIT_STM_TEST(testRecieveWrpcStm, RecieveWrpcContext)


TEST_F(testRecieveWrpcStm, testtest) {
    ASSERT_STATE(Idle);

    test_transition_to<BeltNotRunning>({EventType::EVNT_CTRL_T_STR_PRS_SRT}, {{EventType::EVNT_ACT_BELT_STP}});

    test_transition_to<BeltRunning>({EventType::EVNT_SEN_LB_ST_BLCK}, {{EventType::EVNT_ACT_BELT_FWD}});

    test_transition_to<EStop>({EventType::EVNT_SEN_ESTOP_ON});


}

}
}
}