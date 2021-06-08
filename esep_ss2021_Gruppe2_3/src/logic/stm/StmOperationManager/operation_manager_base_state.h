#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace operationManagerStm {

class OperationManagerBaseState : public BaseBaseState {
public:
    virtual bool str_prs_srt(){return false;}
    virtual bool str_prs_lng(){return false;}
    virtual bool stp_prs_srt(){return false;}
    virtual bool rst_prs_srt(){return false;}
    virtual bool estop_on(){return false;}
    virtual bool conn_lost(){return false;}
    virtual bool estop_off(){return false;}
    virtual bool err(){return false;}
    virtual bool err_gone(){return false;}
    virtual bool wrn(){return false;}
    virtual bool wrn_gone(){return false;}
    virtual bool srv_done(){return false;}

    virtual void entry(){}
    virtual void exit(){}
    virtual void entry_history(){};
    virtual void reset_to_start(){};
};

}
}
}
