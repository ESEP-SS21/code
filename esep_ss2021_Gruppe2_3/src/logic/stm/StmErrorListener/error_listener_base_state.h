#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace StmErrorListener {

class ErrorListenerBaseState: public BaseBaseState {
public:
    virtual bool err(int payload){return false;}
    virtual bool lb_ra_clr(){return false;}
    virtual bool estop_on(){return false;}
    virtual void entry(){};
    virtual void exit(){};
};

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */

