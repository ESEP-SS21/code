#include <logic/stm/StmWpTransfer/wp_transfer_context.h>
#include <logic/stm/StmWpTransfer/wp_transfer_base_state.h>
#include "wp_transfer_states.h"

namespace logic {
namespace stm {
namespace StmWpTransfer {

//put the start state of your stm here
CONTEXT_CTOR(WpTransferContext, Waiting)

using namespace dispatcher;

void WpTransferContext::handle(Event e) {
    auto *state = (WpTransferBaseState *) (_state);
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

} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
