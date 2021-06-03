#include "BeltRunning.h"
#include "BeltNotRunning.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

STATE_INIT(BeltRunning)

bool BeltRunning::lb_st_blck(){
    bool secondary = false;
    if(secondary){
        _datamodel->get_start_height_sec()->enter_workpiece(*_datamodel->get_pending_transfer());
    }else{
        datamodel::Workpiece new_wrpc;
        _datamodel->get_start_height_sec()->enter_workpiece(new_wrpc);
    }
    return true;
}

bool BeltRunning::belt_stp(){
    new(this) BeltNotRunning;
    entry();
    return true;
}

void BeltRunning::entry(){
    _eventSender->send( { EventType::EVNT_ACT_BELT_FWD, 0, false } );
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
