#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace StmWpTransfer {

class WpTransferBaseState: public BaseBaseState {
    WpTransferBaseState() = default;

    virtual void entry(){}
    virtual void exit(){}
    virtual void entry_history(){};
    virtual void reset_to_start(){};
    virtual bool lb_st_blck(){return false;}
    virtual bool belt_stp(){return false;}
    virtual bool wrpc_trans_req(){return false;}
    virtual bool belt_fwd(){return false;}
    virtual bool wrn_gone(){return false;}

};

} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
