#include <logic/stm/StmHeightMeasurement/height_measurement_states.h>

namespace logic {
namespace stm {
namespace StmHeightMeasurement {

STATE_INIT(WaitingForWorkpiece)
STATE_INIT(WaitingForHeight)

bool WaitingForWorkpiece::lb_he_blck() {
    _datamodel->get_start_height_sec()->transfer_first_workpiece();
    exit();
    switch_state<WaitingForHeight>();
    entry();
    _eventSender->send( { EventType::EVNT_SEN_HEIGHT_REQ, 0, true });
    return true;
}

bool WaitingForHeight::he_sensor_he(int payload) {
    if (_datamodel->_unit_type == datamodel::UnitType::PRIMARY) {
        _datamodel->get_start_height_sec()->first_workpiece().height_1 = payload;
        _datamodel->get_start_height_sec()->transfer_first_workpiece();
        exit();
        switch_state<WaitingForWorkpiece>();
        entry();
    }

    if (_datamodel->_unit_type == datamodel::UnitType::SECONDARY) {
        _datamodel->get_start_height_sec()->first_workpiece().height_2 = payload;
        if(_datamodel->get_start_height_sec()->first_workpiece().is_flipped){
            auto enc_wrpc = _datamodel->get_start_height_sec()->first_workpiece().encode();
            _eventSender->send({EventType::EVNT_WRPC_FLP, enc_wrpc.code, true});
        }
        _datamodel->get_start_height_sec()->transfer_first_workpiece();
        exit();
        switch_state<WaitingForWorkpiece>();
        entry();
    }
    return true;
}
}
}
}

