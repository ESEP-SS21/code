#include "recieve_wrpc_context.h"
#include "recieve_wrpc_base_state.h"
#include "receive_wrpc_states.h"

namespace logic {
namespace stm {
namespace receiveWrpcStm {

//put the start state of your stm here
CONTEXT_CTOR(ReceiveWrpcContext, BeltNotRunning)

using namespace dispatcher;

void ReceiveWrpcContext::handle(Event e) {
    if (_datamodel->_operating_mode != datamodel::OperatingMode::RUNNING) {
        return;
    }
    _state->handle(e);
}

}
}
}
