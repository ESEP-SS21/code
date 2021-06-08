#include "error_listener_states.h"

namespace logic {
namespace stm {
namespace StmErrorListener {

STATE_INIT(WaitingForError)

bool WaitingForError::err(int payload){
    _datamodel->_pending_error = datamodel::Error(payload);
    switch_state<WaitingForResolve>();
    return true;
}

STATE_INIT(WaitingForResolve)

bool WaitingForResolve::lb_ra_clr(){
    if(_datamodel->_pending_error == datamodel::Error::RAMP_FULL){
        _datamodel->_pending_error = datamodel::Error::NO_ERROR;
        switch_state<WaitingForError>();
        _eventSender->send({EventType::EVNT_ERR_GONE});
    }
    return true;
}

} /* namespace StmErrorListener */
} /* namespace stm */
} /* namespace logic */



