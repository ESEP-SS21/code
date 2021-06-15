#include "RampFull.h"
#include "WaitingForWrpc.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(RampFull)

bool RampFull::lb_sw_blck() {
    bool handled = false;
    if (_datamodel->_unit_type == UnitType::SECONDARY) {
        //section cant be empty
        if (_datamodel->get_height_switch_sec()->workpiece_count() == 0) {
            std::cout << "MISSING WORKPIECE IN DATAMODEL" << std::endl;
            return handled;
        }
        Workpiece unchecked_wrpc = _datamodel->get_height_switch_sec()->first_workpiece();
        if (!_datamodel->wrpc_fits_order(unchecked_wrpc)) {
            _eventSender->send(
                    { EventType::EVNT_ERR, static_cast<int>(::logic::datamodel::Error::RAMP_FULL), true });
            handled = true;
        }
    }
    return handled;
}

bool RampFull::lb_ra_clr() {
    exit();
    _eventSender->send( { EventType::EVNT_WRN_GONE, 0, true });
    switch_state<WaitingForWrpc>();
    _datamodel->_ramp_full = false;
    entry();
    return true;
}

void RampFull::exit() {

}

void RampFull::entry() {

}

bool RampFull::has_super_exit_with_lb_sw_blck_from_ramp_full() {
    return true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
