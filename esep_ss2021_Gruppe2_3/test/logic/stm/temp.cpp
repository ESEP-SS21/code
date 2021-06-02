#include "logic/stm/testStm/test_base_state.h"
#include "logic/stm/testStm/test_context.h"
#include <gtest/gtest.h>


#include "../../TestUtils.h"

using namespace ::logic::stm::testStm;

TEST(STM, testtest) {
    TestContext t;
    std::cout << "current state:" << t.currentState() << std::endl;
    t.handle({EventType::EVNT_ACK,0,false});
}
