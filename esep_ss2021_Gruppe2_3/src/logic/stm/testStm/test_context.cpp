#include "test_context.h"
#include "states/state_a.h"
#include "../test/logic/stm/stm_test_client.h"

namespace logic {
namespace stm {
namespace testStm {

TestContext::TestContext(std::shared_ptr<IEventSender> eventSender) :
    BaseContext(std::make_shared<StateA>(eventSender)) {
}

void TestContext::handle(Event e) {
    std::dynamic_pointer_cast<TestBaseState>(_state)->tick();
}

}
}
}
