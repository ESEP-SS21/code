#include <logic/stm/StmAnswerTransferReq/answer_transfer_req_context.h>
#include <logic/stm/StmAnswerTransferReq/answer_transfer_req_base_state.h>
#include "answer_transfer_req_states.h"

namespace logic {
namespace stm {
namespace StmAnswerTransferReq {

//put the start state of your stm here
CONTEXT_CTOR(AnswerTransferReqContext, Waiting)

using namespace dispatcher;

void AnswerTransferReqContext::handle(Event e) {
    auto *state = (AnswerTransferReqBaseState *) (_state);
    if(_datamodel->_operating_mode != datamodel::OperatingMode::RUNNING){
        return;
    }
    switch (e.type) {
        case EventType::EVNT_SEN_LB_HE_BLCK:
            state->lb_he_blck();
            return;
        case EventType::EVNT_WRPC_TRNS_RQ:
            state->wrpc_trns_rq(e.payload);
            return;
        default:
            return;
    }
}

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
