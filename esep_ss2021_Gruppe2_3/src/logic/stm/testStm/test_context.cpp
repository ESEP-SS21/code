#include "test_context.h"
#include "states/state_a.h"
#include "../test/logic/stm/util/stm_test_client.h"

namespace logic {
namespace stm {
namespace testStm {

CONTEXT_CTOR(TestContext)

void TestContext::handle(Event e) {
    ((TestBaseState*)_state)->tick(e.payload);
}

}
}
}
