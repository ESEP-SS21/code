#include "top_level.h"
#include "sub_operating.h"

namespace logic {
namespace stm {
// change the namespace to the namespace of your substm
namespace sortWrpcStm {

//put the start state of your Sub Stm here
//add the methods to call in your substate here
INIT_SUB_STM(Running, SubOperating)

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

bool Running::lb_sw_blck(){
    return _substate->lb_sw_blck();
}
bool Running::lb_sw_clr(){
    return _substate->lb_sw_clr();
}
bool Running::lb_ra_clr(){
    return _substate->lb_ra_clr();
}
bool Running::tim_alrt(int tim_id){
    return _substate->tim_alrt(tim_id);
}

void Running::entry_history(){
    //TODO maybe incorrect
    if (_substate == nullptr)
        entry_sub_start_node();
    _substate->entry();
    _substate->entry_history();
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

bool Error::lb_ra_clr(){
    _ramp_already_cleared = true;
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



} /* namespace sortWrpcStm */
} /* namespace stm */
} /* namespace logic */



