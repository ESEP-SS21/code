#pragma once

#include "answer_transfer_req_base_state.h"

namespace logic {
namespace stm {
namespace StmAnswerTransferReq {

class Waiting: public AnswerTransferReqBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
};

class WaitingForSpace: public AnswerTransferReqBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
};

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
