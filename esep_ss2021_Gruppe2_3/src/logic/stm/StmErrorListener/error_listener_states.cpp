#include "error_listener_states.h"

namespace logic {
namespace stm {
namespace StmErrorListener {

STATE_INIT(WaitingForError)

bool WaitingForError::err(int payload){
    _datamodel->_pending_error = datamodel::Error(payload);
    switch_state<WaitingForResolve>();
    entry();
    return true;
}

void WaitingForError::entry(){
    _datamodel->_pending_error = datamodel::Error::NO_ERROR;
}

STATE_INIT(WaitingForResolve)

bool WaitingForResolve::lb_ra_clr(){
    if(_datamodel->_pending_error == datamodel::Error::RAMP_FULL){
        _eventSender->send({EventType::EVNT_ERR_GONE});
        switch_state<WaitingForError>();
        entry();
    }
    return true;
}

bool WaitingForResolve::estop_on(){
    switch_state<WaitingForError>();
    entry();
    return true;
}

} /* namespace StmErrorListener */
} /* namespace stm */
} /* namespace logic */



