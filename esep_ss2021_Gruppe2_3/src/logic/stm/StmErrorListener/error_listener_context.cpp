#include "error_listener_context.h"
#include "error_listener_states.h"

namespace logic {
namespace stm {
namespace StmErrorListener {

//put the start state of your stm here
CONTEXT_CTOR(ErrorListenerContext, WaitingForError)

using namespace dispatcher;

void ErrorListenerContext::handle(Event e) {
    auto *state = (ErrorListenerBaseState *) (_state);
    switch(e.type){
        case(EventType::EVNT_ERR):
            state->err(e.payload);
            return;
        case(EventType::EVNT_SEN_LB_RA_CLR):
            state->lb_ra_clr();
            return;
        case(EventType::EVNT_SEN_ESTOP_ON):
            state->estop_on();
            return;
        case(EventType::EVNT_CONN_LOST):
            state->estop_on();
            return;
        default:
            return;
    }
}

} /* namespace StmMetalDetection */
} /* namespace stm */
} /* namespace logic */


