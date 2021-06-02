#include "test_context.h"
#include "states/state_a.h"
#include "../test/logic/stm/stm_test_client.h"

namespace logic {
namespace stm {
namespace testStm {

CONTEXT_CTOR(TestContext, StateA)

void TestContext::handle(Event e) {
    ((TestBaseState*)_state)->tick(e.payload);
}

}
}
}
