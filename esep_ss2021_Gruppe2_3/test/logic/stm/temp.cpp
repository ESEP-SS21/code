#include "logic/stm/testStm/test_base_state.h"
#include "logic/stm/testStm/test_context.h"
#include <gtest/gtest.h>
#include "stm_test_client.h"


#include "../../TestUtils.h"

using namespace ::logic::stm;

TEST(STM, testtest) {
    testStm::TestContext t(std::make_shared<StmTestClient>());
    std::cout << "current state:" << t.currentState() << std::endl;
    t.handle({EventType::EVNT_ACK,0,false});
}
