#include <logic/stm/StmHeightMeasurement/height_measurement_states.h>
#include <iostream>

namespace logic {
namespace stm {
namespace StmHeightMeasurement {

STATE_INIT(WaitingForWorkpiece)
STATE_INIT(WaitingForHeight)

bool WaitingForWorkpiece::lb_he_blck() {
    if(_datamodel->get_start_height_sec()->empty()){
        std::cout << "Unexpected wrpc in " << name <<std::endl;
        return true;
    }
    _datamodel->get_start_height_sec()->transfer_first_workpiece();
    _datamodel->_belt_blocked = false;
    exit();
    switch_state<WaitingForHeight>();
    entry();
    return true;
}

bool WaitingForHeight::he_sensor_he(int payload) {
    exit();
    auto hs_section = _datamodel->get_height_switch_sec();
    if (_datamodel->_unit_type == datamodel::UnitType::PRIMARY) {
        hs_section->last_workpiece().height_1 = payload;
        hs_section->last_workpiece().determine_type();
    } else {
        hs_section->last_workpiece().height_2 = payload;
        hs_section->last_workpiece().determine_type();
        if (hs_section->last_workpiece().is_flipped && _datamodel->wrpc_fits_order(hs_section->last_workpiece())) {
            auto enc_wrpc = hs_section->first_workpiece().encode();
            _eventSender->send( { EventType::EVNT_WRPC_FLP, enc_wrpc.code, true });
        }
    }
    switch_state<WaitingForWorkpiece>();
    entry();
    return true;
}

void WaitingForHeight::entry() {
    _eventSender->send( { EventType::EVNT_SEN_HEIGHT_REQ });
}

} /* namespace StmHeightMeasurement */
} /* namespace stm */
} /* namespace logic */

