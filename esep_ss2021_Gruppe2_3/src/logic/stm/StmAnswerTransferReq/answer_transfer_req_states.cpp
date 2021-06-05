#include <logic/stm/StmAnswerTransferReq/answer_transfer_req_states.h>

namespace logic {
namespace stm {
namespace StmAnswerTransferReq {

STATE_INIT(Waiting)
STATE_INIT(WaitingForSpace)

bool Waiting::wrpc_trns_rq() {
    return false;
}

bool WaitingForSpace::wrpc_trns_rq() {
    return false;
}

bool WaitingForSpace::lb_he_blck() {
    return false;
}

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
