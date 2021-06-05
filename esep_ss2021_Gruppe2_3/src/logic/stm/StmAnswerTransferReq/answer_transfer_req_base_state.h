#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace StmAnswerTransferReq {

class AnswerTransferReqBaseState: public BaseBaseState {
public:
    virtual bool wrpc_trns_rq(){return false;}
    virtual bool lb_he_blck(){return false;}
};

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
