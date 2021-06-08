#include <logic/stm/StmHeightMeasurement/height_measurement_states.h>

namespace logic {
namespace stm {
namespace StmHeightMeasurement {

STATE_INIT(WaitingForWorkpiece)
STATE_INIT(WaitingForHeight)

bool WaitingForWorkpiece::lb_he_blck() {
    exit();
    _datamodel->get_start_height_sec()->transfer_first_workpiece();
    _datamodel->_belt_blocked = false;
    switch_state<WaitingForHeight>();
    entry();
    _eventSender->send( { EventType::EVNT_SEN_HEIGHT_REQ, 0, true });
    return true;
}

bool WaitingForHeight::he_sensor_he(int payload) {
    exit();
    if (_datamodel->_unit_type == datamodel::UnitType::PRIMARY) {
        auto section = _datamodel->get_start_height_sec();
        if (section->empty()) {
            std::cout << name << " No workpiece in section! " << std::endl;
        } else {
            section->first_workpiece().height_1 = payload;
            section->transfer_first_workpiece();
        }
        switch_state<WaitingForWorkpiece>();
        entry();
    }

    if (_datamodel->_unit_type == datamodel::UnitType::SECONDARY) {
        auto section = _datamodel->get_start_height_sec();
        if (section->empty()) {
            std::cout << name << " No workpiece in section! " << std::endl;
        } else {
            section->first_workpiece().height_2 = payload;
            if (section->first_workpiece().is_flipped) {
                auto enc_wrpc = section->first_workpiece().encode();
                _eventSender->send( { EventType::EVNT_WRPC_FLP, enc_wrpc.code, true });
            }
            section->transfer_first_workpiece();
        }
        switch_state<WaitingForWorkpiece>();
        entry();
    }
    return true;
}
void WaitingForHeight::entry() {
    _eventSender->send( { EventType::EVNT_SEN_HEIGHT_REQ });

}
}
}
}

