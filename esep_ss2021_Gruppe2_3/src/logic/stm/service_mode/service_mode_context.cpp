#include "service_mode_context.h"
#include "service_mode_states.h"

namespace logic {
namespace stm {
namespace ServiceModeStm {

//put the start state of your stm here
CONTEXT_CTOR(ServiceModeContext, ServiceModeState)

using namespace dispatcher;

void ServiceModeContext::handle(Event e) {
    if (_datamodel->_operating_mode != datamodel::OperatingMode::SERVICE) {
        return;
    }
    _state->handle(e);
}

}
}
}
