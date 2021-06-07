#include <logic/stm/StmRecieveWrpc/sub_belt_states.h>


namespace logic {
namespace stm {
namespace recieveWrpcStm {

STATE_INIT(BeltNotRunning)
STATE_INIT(BeltRunning)

bool BeltNotRunning::lb_st_blck(){
    bool belt_blocked = _datamodel->_belt_blocked;
    if(_datamodel->_unit_type == UnitType::SECONDARY){
        _datamodel->get_start_height_sec()->enter_workpiece(*_datamodel->get_pending_transfer());
    }else{
        datamodel::Workpiece new_wrpc;
        _datamodel->get_start_height_sec()->enter_workpiece(new_wrpc);
    }
    if(!belt_blocked){
        switch_state<BeltRunning>();
        entry();
    }
    return true;
}

bool BeltNotRunning::belt_fwd(){
    switch_state<BeltRunning>();
    entry();
    return true;
}

void BeltNotRunning::entry(){
    _datamodel->_belt_state = datamodel::BeltState::RUNNING;
    _eventSender->send( { EventType::EVNT_ACT_BELT_STP, 0, false } );
};

void BeltNotRunning::entry_history(){
    entry();
}

void BeltNotRunning::reset_to_start(){
    entry();
}




bool BeltRunning::lb_st_blck(){
    if(_datamodel->_unit_type == UnitType::SECONDARY){
        _datamodel->get_start_height_sec()->enter_workpiece(*_datamodel->get_pending_transfer());
    }else{
        datamodel::Workpiece new_wrpc;
        _datamodel->get_start_height_sec()->enter_workpiece(new_wrpc);
    }
    return true;
}

bool BeltRunning::belt_stp(){
    switch_state<BeltNotRunning>();
    entry();
    return true;
}

void BeltRunning::entry(){
    _datamodel->_belt_state = datamodel::BeltState::RUNNING;
    _eventSender->send( { EventType::EVNT_ACT_BELT_FWD, 0, false } );
};

void BeltRunning::entry_history(){
    entry();
}

void BeltRunning::reset_to_start(){
    switch_state<BeltNotRunning>();
    entry();
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
