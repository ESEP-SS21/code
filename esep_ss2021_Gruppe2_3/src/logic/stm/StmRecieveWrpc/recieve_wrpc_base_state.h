#pragma once

#include "../base_base_state.h"


namespace logic {
namespace stm {
namespace recieveWrpcStm {

class RecieveWrpcBaseState : public BaseBaseState {

public:
    RecieveWrpcBaseState() = default;

    virtual bool lb_st_blck(){return false;}
    virtual bool belt_stp(){return false;}
    virtual bool belt_fwd(){return false;}
    virtual bool estop_on(){return false;}
    virtual void entry(){}
    virtual void exit(){}
};

}
}
}
