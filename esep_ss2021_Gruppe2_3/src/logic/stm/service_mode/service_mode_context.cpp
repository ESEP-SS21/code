#include "service_mode_context.h"
#include "service_mode_base_state.h"
#include "service_mode_states.h"

namespace logic {
namespace stm {
namespace stm_service_mode {

//put the start state of your stm here
CONTEXT_CTOR(ServiceModeContext, StartState)

using namespace dispatcher;

void ServiceModeContext::handle(Event e) {
    if(_datamodel->_operating_mode != datamodel::OperatingMode::SERVICE){
        return;
    }

    if(e.type == EventType::EVNT_CTRL_T_STP_PRS_LNG) {
        _state->exit();
        new (_state) StartState;
        _state->entry();
        dynamic_cast<ServiceModeBaseState*>(_state)->end_service();
        return;
    }

    _state->handle(e);
}

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
