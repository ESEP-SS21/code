#include "TestContext.hpp"
#include <logic/stm/testStm/states/StateA.h>

namespace logic {
namespace stm {
namespace testStm {

TestContext::TestContext() :
        BaseContext(std::make_shared<StateA>()) {
}

void TestContext::handle(Event e) {
}

std::string TestContext::currentState() {
    return "asdf";
}
}
}
}
