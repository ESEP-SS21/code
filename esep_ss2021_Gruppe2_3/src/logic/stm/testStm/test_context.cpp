#include "test_context.h"
#include "states/state_a.h"
#include "../test/logic/stm/stm_test_client.h"

namespace logic {
namespace stm {
namespace testStm {

TestContext::TestContext(std::shared_ptr<IEventSender> eventSender,std::shared_ptr<UnitData> datamodel) :
    BaseContext(std::make_shared<StateA>(eventSender,datamodel)) {
}

void TestContext::handle(Event e) {
    _state->tick(e.payload);
}

}
}
}
