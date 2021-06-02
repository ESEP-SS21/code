#include "logic/stm/testStm/TestBaseState.hpp"
#include "logic/stm/testStm/TestContext.hpp"
#include <gtest/gtest.h>


#include "../../TestUtils.h"

using namespace ::logic::stm::testStm;

TEST(WorkpieceTest, DeterminedTypeShouldBeCorrct) {
    TestContext t;
    t.handle({EventType::EVNT_ACK,0,false});
}
