#include "logic/stm/testStm/test_base_state.h"
#include "logic/stm/testStm/test_context.h"
#include "logic/stm/testStm/states/state_a.h"
#include "logic/stm/testStm/states/sub_stm_b.h"
#include <gtest/gtest.h>
#include <logic/stm/testStm/states/substate_c.h>
#include "stm_test_client.h"
#include "stm_test_base.h"

using namespace ::logic::stm;

INIT_STM_TEST(test_TestSTM, testStm::TestContext)

TEST_F(test_TestSTM, testtest) {
    std::cout << "current state:" << context.currentState() << std::endl;
    ASSERT_EQ(context.currentState(), testStm::StateA::name);
    Event e{EventType::EVNT_ACK, 44};

    context.handle(e);
    ASSERT_EQ(context.currentState(), testStm::SubStateC::name);
    std::cout << "completet name: " << context.str() << std::endl;
    Event recieved = client.get_last_event();
    ASSERT_EQ(recieved, e);
    std::cout << "current state:" << context.currentState() << std::endl;

    context.handle(e);
    ASSERT_EQ(context.currentState(), testStm::SubStateC::name);
    recieved = client.get_last_event();
    ASSERT_EQ(recieved, e);
    std::cout << "current state:" << context.currentState() << std::endl;
}
