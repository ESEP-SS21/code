#include "logic/stm/testStm/test_base_state.h"
#include "logic/stm/testStm/test_context.h"
#include "logic/stm/testStm/states/state_a.h"
#include "logic/stm/testStm/states/state_b.h"
#include <gtest/gtest.h>
#include <logic/stm/testStm/states/state_c.h>
#include "stm_test_client.h"


#include "../../TestUtils.h"

using namespace ::logic::stm;

TEST(STM, testtest) {
    auto client = std::make_shared<StmTestClient>();
    testStm::TestContext t(client.get(), nullptr);

    std::cout << "current state:" << t.currentState() << std::endl;
    ASSERT_EQ(t.currentState(), testStm::StateA::name);
    Event e{EventType::EVNT_ACK, 44, false};

    t.handle(e);
    ASSERT_EQ(t.currentState(), testStm::StateC::name);
    Event recieved = client->get_last_event();
    ASSERT_EQ(recieved, e);
    std::cout << "current state:" << t.currentState() << std::endl;

    t.handle(e);
    ASSERT_EQ(t.currentState(), testStm::StateC::name);
    recieved = client->get_last_event();
    ASSERT_EQ(recieved, e);
    std::cout << "current state:" << t.currentState() << std::endl;
}
