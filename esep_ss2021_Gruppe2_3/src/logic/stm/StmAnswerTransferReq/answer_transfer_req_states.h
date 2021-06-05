#pragma once

#include "answer_transfer_req_base_state.h"

namespace logic {
namespace stm {
namespace StmAnswerTransferReq {

class Waiting: public AnswerTransferReqBaseState {
public:
    STATE_HEADER_INIT
    bool wrpc_trns_rq(int payload) override;
};

class WaitingForSpace: public AnswerTransferReqBaseState {
public:
    STATE_HEADER_INIT
    bool lb_he_blck() override;
    void reset_to_start() override;
};

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
