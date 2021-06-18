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
    if (_datamodel->_operating_mode != datamodel::OperatingMode::RUNNING) {
        return;
    }
    switch (e.type) {
    case EventType::EVNT_TIM_ALRT:
        state->tim_alrt(e.payload);
        return;
    case EventType::EVNT_SEN_LB_EN_BLCK:
        state->lb_en_blck();
        return;
    case EventType::EVNT_ACK:
        state->ack();
        return;
    case EventType::EVNT_HIST:
        state->entry_history();
        return;
    case EventType::EVNT_RST_TO_SRT:
        state->reset_to_start();
        return;
    case EventType::EVNT_SEN_LB_EN_CLR:
        state->lb_en_clr();
        return;
    default:
        return;
    }
}
} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
