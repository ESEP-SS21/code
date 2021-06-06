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
    if(_datamodel->_operating_mode != datamodel::OperatingMode::RUNNING){
        return;
    }
    _state->handle(e);
}

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
