#include "recieve_wrpc_context.h"
#include "recieve_wrpc_base_state.h"
#include "sub_belt_states.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

//put the start state of your stm here
CONTEXT_CTOR(RecieveWrpcContext, BeltNotRunning)

using namespace dispatcher;

void RecieveWrpcContext::handle(Event e) {
    if (_datamodel->_operating_mode != datamodel::OperatingMode::RUNNING) {
        return;
    }
    _state->handle(e);
}

}
}
}
