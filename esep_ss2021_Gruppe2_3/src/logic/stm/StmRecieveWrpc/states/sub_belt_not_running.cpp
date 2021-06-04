#include <logic/stm/StmRecieveWrpc/states/sub_belt_not_running.h>
#include <logic/stm/StmRecieveWrpc/states/sub_belt_running.h>

namespace logic {
namespace stm {
namespace recieveWrpcStm {

STATE_INIT(BeltNotRunning)

bool BeltNotRunning::lb_st_blck(){
    // todo get state from datamodel
    bool secondary = false;
    bool belt_blocked = _datamodel->get_belt_blocked();
    if(secondary){
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
    _datamodel->set_belt_state(datamodel::BeltState::RUNNING);
    _eventSender->send( { EventType::EVNT_ACT_BELT_STP, 0, false } );
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
