#include "test_context.h"
#include "states/state_a.h"

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
