#include "RampFull.h"
#include "WaitingForWrpc.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(RampFull)

bool RampFull::lb_sw_blck(){
    bool handled = false;
    if(_datamodel->_unit_type == UnitType::SECONDARY) {
       Workpiece unchecked_wrpc = _datamodel->get_height_switch_sec()->first_workpiece();
       if(!_datamodel->wrpc_fits_order(unchecked_wrpc)) {
           _eventSender->send(dispatcher::Event::CreateError(EventType::EVNT_SEN_LB_RA_CLR));
           handled = true;
       }
    }
    return handled;
}

bool RampFull::lb_ra_clr(){
    exit();
    switch_state<WaitingForWrpc>();
    _datamodel->_ramp_full = false;
    entry();
    return true;
}

void RampFull::exit(){
    _eventSender->send( { EventType::EVNT_WRN_GONE, 0, false } );
}

void RampFull::entry(){
    _eventSender->send( { EventType::EVNT_WRN, 0, false } );
    _datamodel->_ramp_full = true;
}

bool RampFull::has_super_exit_with_lb_sw_blck_from_ramp_full() {
    return true;
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
