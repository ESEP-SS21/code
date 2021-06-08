#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace StmWpTransfer {

class WpTransferBaseState: public BaseBaseState {
public:
    WpTransferBaseState() = default;

    virtual bool ack(){return false;}
    virtual void entry(){}
    virtual void entry_history(){};
    virtual void reset_to_start(){};
    virtual bool lb_st_blck(){return false;}
    virtual bool belt_stp(){return false;}
    virtual bool wrpc_trans_req(){return false;}
    virtual bool belt_fwd(){return false;}
    virtual bool wrn_gone(){return false;}
    virtual bool lb_en_clr(){return false;}
    virtual bool tim_alrt(int tim_id){return false;}
    virtual bool lb_en_blck(){return false;}

};

} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
