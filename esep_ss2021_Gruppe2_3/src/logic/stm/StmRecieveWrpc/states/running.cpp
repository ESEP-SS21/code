#include "error.h"
#include "running.h"
#include "idle.h"
#include "estop.h"
#include "service.h"
#include "BeltNotRunning.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {


INIT_SUB_STM(Running, BeltNotRunning)

bool Running::err(){
    if(!_substate->err()){
        _substate->exit();
        new (this) Error;
        exit();
    }
    return true;
}

bool Running::estop_on(){
    if(!_substate->estop_on()){
        _substate->exit();
        new (this) EStop;
        exit();
    }
    return true;
}
bool Running::stp_prs_srt(){
   return _substate->stp_prs_srt();
}
bool Running::lb_st_blck(){
    return _substate->lb_st_blck();
}
bool Running::belt_stp(){
    return _substate->belt_stp();
}
bool Running::belt_fwd(){
    return _substate->belt_fwd();
}

void Running::entry_history(){
    _substate->entry();
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
