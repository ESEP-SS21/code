#include "test_context.h"
#include "states/state_a.h"
#include "../test/logic/stm/stm_test_client.h"

namespace logic {
namespace stm {
namespace testStm {

TestContext::TestContext(IEventSender *eventSender, UnitData *datamodel) :
    BaseContext(new StateA()) {
    _state->SetData(eventSender, datamodel);
}

void TestContext::handle(Event e) {
    ((TestBaseState*)_state)->tick(e.payload);
}

}
}
}
