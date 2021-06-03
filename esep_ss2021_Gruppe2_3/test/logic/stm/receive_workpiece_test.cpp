#include <gtest/gtest.h>
#include <logic/stm/StmRecieveWrpc/states/sub_belt_not_running.h>
#include <logic/stm/StmRecieveWrpc/states/sub_belt_running.h>
#include <logic/stm/StmRecieveWrpc/states/estop.h>
#include <logic/stm/StmRecieveWrpc/states/idle.h>
#include "logic/stm/StmRecieveWrpc/recieve_wrpc_context.h"
#include "stm_test_client.h"

#include "stm_test_base.h"

using namespace ::logic::stm::recieveWrpcStm;

INIT_STM_TEST(testRecieveWrpcStm, RecieveWrpcContext)

TEST_F(testRecieveWrpcStm, testtest) {
    ASSERT_STATE(Idle);

    context.handle({EventType::EVNT_CTRL_T_STR_PRS_SRT});
    ASSERT_STATE(BeltRunning);

    context.handle(Event{EventType::EVNT_SEN_LB_ST_BLCK});
    ASSERT_STATE(BeltRunning);
    ASSERT_EQ(client.get_last_event().type, EventType::EVNT_ACT_BELT_STP);
    ASSERT_TRUE(client.empty());

    context.handle(Event{EventType::EVNT_SEN_ESTOP_ON});
    ASSERT_STATE(EStop);
    ASSERT_TRUE(client.empty());

}
