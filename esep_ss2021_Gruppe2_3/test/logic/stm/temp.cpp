#include "logic/stm/testStm/test_base_state.h"
#include "logic/stm/testStm/test_context.h"
#include "logic/stm/testStm/states/state_a.h"
#include <gtest/gtest.h>
#include "stm_test_client.h"


#include "../../TestUtils.h"

using namespace ::logic::stm;

TEST(STM, testtest) {
    testStm::TestContext t(std::make_shared<StmTestClient>());
    std::cout << "current state:" << t.currentState() << std::endl;
    ASSERT_EQ(t.currentState(), testStm::StateA::name);
    t.handle({EventType::EVNT_ACK, 44, false});
}
