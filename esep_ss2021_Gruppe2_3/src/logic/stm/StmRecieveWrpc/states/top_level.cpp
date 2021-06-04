#include "top_level.h"
#include "sub_belt_not_running.h"

namespace logic {
namespace stm {
// change the namespace to the namespace of your substm
namespace recieveWrpcStm {

//put the start state of your Sub Stm here
//add the methods to call in your substate here
INIT_SUB_STM(Running, BeltNotRunning)

bool Running::err(){
    if(!_substate->err()){
        _substate->exit();
        switch_state<Error>();
        exit();
    }
    return true;
}

bool Running::estop_on(){
    if(!_substate->estop_on()){
        _substate->exit();
        switch_state<EStop>();
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
    //TODO maybe incorrect
    if (_substate == nullptr)
        entry_sub_start_node();
    _substate->entry();
}

//ERROR
STATE_INIT(Error)

bool Error::estop_on(){
    switch_state<EStop>();
    entry();
    return true;
}

bool Error::all_err_gone(){
    switch_state<Running>();
    entry();
    entry_sub_start_node();
    return true;
}

STATE_INIT(EStop)

bool EStop::rst_prs_srt(){
    if(_datamodel->get_estop_count() == 0){
        switch_state<Idle>();
        entry();
        return true;
    }
    return false;
}

//IDLE
STATE_INIT(Idle)

bool Idle::estop_on(){
    switch_state<EStop>();
    entry();
    return true;
}

bool Idle::str_prs_srt(){
    switch_state<Running>();
    entry();
    entry_history();
    return true;
}

bool Idle::str_prs_lng(){
    switch_state<Service>();
    entry();
    return true;
}
//SERVICE
STATE_INIT(Service)

bool Service::estop_on(){
    switch_state<EStop>();
    entry();
    return true;
}

bool Service::srv_done(){
    switch_state<Idle>();
    entry();
    return true;
}



} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */



