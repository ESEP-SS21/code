#include "TestContext.hpp"
#include <logic/stm/testStm/states/StateA.h>
#include <logic/stm/testStm/TestBaseState.hpp>

namespace logic {
namespace stm {
namespace testStm {

TestContext::TestContext() :
        BaseContext(std::make_shared<StateA>()) {
}

void TestContext::handle(Event e) {
    std::dynamic_pointer_cast<TestBaseState>(_state)->tick();
}

}
}
}
