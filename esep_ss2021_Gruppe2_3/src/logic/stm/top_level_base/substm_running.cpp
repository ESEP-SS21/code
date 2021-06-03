#include "error.h"
#include "idle.h"
#include "estop.h"
#include "service.h"
#include "substm_running.h"

namespace logic {
namespace stm {
namespace top_level {



template<typename T>
bool Running<T>::err(){
    if(!this->_substate->err()){
        this->_substate->exit();
        new (this) Error<T>;
        this->exit();
    }
    return true;
}

template<typename T>
bool Running<T>::estop_on(){
    if(!this->_substate->estop_on()){
        this->_substate->exit();
        new (this) EStop<T>;
        this->exit();
    }
    return true;
}

template<typename T>
bool Running<T>::stp_prs_srt(){
   return this->_substate->stp_prs_srt();
}

template<typename T>
bool Running<T>::lb_st_blck(){
    return this->_substate->lb_st_blck();
}

template<typename T>
bool Running<T>::belt_stp(){
    return this->_substate->belt_stp();
}

template<typename T>
bool Running<T>::belt_fwd(){
    return this->_substate->belt_fwd();
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
