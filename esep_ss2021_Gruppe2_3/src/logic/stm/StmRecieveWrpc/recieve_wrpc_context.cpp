#include "recieve_wrpc_context.h"
#include "recieve_wrpc_base_state.h"
#include "states/sub_belt_not_running.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

//put the start state of your stm here
CONTEXT_CTOR(RecieveWrpcContext, BeltNotRunning)

using namespace dispatcher;

void RecieveWrpcContext::handle(Event e) {
    auto *state = (RecieveWrpcBaseState *) (_state);
    if(_datamodel->_operating_mode != datamodel::OperatingMode::RUNNING){
        return;
    }
    switch (e.type) {
        case EventType::EVNT_SEN_LB_ST_BLCK:
            state->lb_st_blck();
            return;
        case EventType::EVNT_ACT_BELT_STP:
            state->belt_stp();
            return;
        case EventType::EVNT_ACT_BELT_FWD:
            state->belt_fwd();
            return;
        case EventType::EVNT_HIST:
            state->entry_history();
            return;
        case EventType::EVNT_RST_TO_SRT:
            state->reset_to_start();
            return;
        default:
            return;
    }
}

}
}
}
