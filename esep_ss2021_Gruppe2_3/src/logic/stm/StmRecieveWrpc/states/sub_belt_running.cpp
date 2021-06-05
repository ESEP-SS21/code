#include <logic/stm/StmRecieveWrpc/states/sub_belt_not_running.h>
#include <logic/stm/StmRecieveWrpc/states/sub_belt_running.h>

namespace logic {
namespace stm {
namespace recieveWrpcStm {

STATE_INIT(BeltRunning)

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

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
