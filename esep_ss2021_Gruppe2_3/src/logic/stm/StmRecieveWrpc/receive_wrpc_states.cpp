#include <logic/stm/StmRecieveWrpc/receive_wrpc_states.h>


namespace logic {
namespace stm {
namespace receiveWrpcStm {

using namespace dispatcher;

STATE_INIT(BeltNotRunning)

bool BeltNotRunning::handle(const Event &event) {
    switch (event.type) {
        case EventType::EVNT_HIST:
            entry();
            return true;
        case EventType::EVNT_RST_TO_SRT:
            entry();
            return true;
        case EventType::EVNT_ACT_BELT_FWD:
            switch_state<BeltRunning>();
            entry();
            return true;
        case EventType::EVNT_SEN_LB_ST_BLCK: {
            bool belt_blocked = _datamodel->_belt_blocked;
            if (_datamodel->_unit_type == UnitType::SECONDARY) {
                if(_datamodel->get_pending_transfer().get() == 0){
                    std::cout << "Unexpected wrpc in " << name <<std::endl;
                    return true;
                }
                _datamodel->get_start_height_sec()->enter_workpiece(*_datamodel->get_pending_transfer());
                _datamodel->_belt_blocked = true;
            } else {
                datamodel::Workpiece new_wrpc;
                _datamodel->get_start_height_sec()->enter_workpiece(new_wrpc);
            }
            if (!belt_blocked) {
                switch_state<BeltRunning>();
                entry();
            }
            return true;
        }
        default:
            return false;
    }
}

void BeltNotRunning::entry() {
    _datamodel->_belt_state = datamodel::BeltState::RUNNING;
    //_eventSender->send({EventType::EVNT_ACT_BELT_STP, 0, false});
}

STATE_INIT(BeltRunning)

bool BeltRunning::handle(const Event &event) {
    switch (event.type) {
        case EventType::EVNT_HIST:
            entry();
            return true;
        case EventType::EVNT_RST_TO_SRT:
            switch_state<BeltNotRunning>();
            entry();
            return true;
        case EventType::EVNT_SEN_LB_ST_BLCK:
            if (_datamodel->_unit_type == UnitType::SECONDARY) {
                if(_datamodel->get_pending_transfer().get() == 0){
                    std::cout << "Unexpected wrpc in " << name <<std::endl;
                    return true;
                }
                _datamodel->get_start_height_sec()->enter_workpiece(*_datamodel->get_pending_transfer());
                _datamodel->_belt_blocked = true;
            } else {
                datamodel::Workpiece new_wrpc;
                _datamodel->get_start_height_sec()->enter_workpiece(new_wrpc);
            }
            return true;
        case EventType::EVNT_ACT_BELT_STP:
            switch_state<BeltNotRunning>();
            entry();
            return true;
        default:
            return false;
    }
}

void BeltRunning::entry() {
    _datamodel->_belt_state = datamodel::BeltState::RUNNING;
    _eventSender->send({EventType::EVNT_ACT_BELT_FWD, 0, false});
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
