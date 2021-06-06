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
    if(_datamodel->_operating_mode != datamodel::OperatingMode::RUNNING){
        return;
    }
    _state->handle(e);
}

} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
