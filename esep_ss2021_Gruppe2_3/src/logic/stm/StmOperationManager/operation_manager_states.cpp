#include "operation_manager_states.h"

namespace logic {
namespace stm {
namespace operationManagerStm {

STATE_INIT(Running)
bool Running::err(){
    switch_state<Error>();
}

//ERROR
STATE_INIT(Error)
bool Error::estop_on(){
    switch_state<EStop>();
    entry();
    return true;
}

bool Error::err_gone(){
    switch_state<Running>();
    entry();
    return true;
}

STATE_INIT(EStop)
bool EStop::rst_prs_srt(){
    if(_datamodel->_estop_count == 0){
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

}
}
}




