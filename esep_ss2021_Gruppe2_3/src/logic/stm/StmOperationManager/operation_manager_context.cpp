#include "operation_manager_context.h"
#include "operation_manager_states.h"
#include "operation_manager_base_state.h"

namespace logic {
namespace stm {
namespace operationManagerStm {

CONTEXT_CTOR(OperationManagerContext, Idle)

using namespace dispatcher;

void OperationManagerContext::handle(Event e) {
    switch (e.type) {
    case EventType::EVNT_CTRL_T_STR_PRS_SRT:
        state->str_prs_srt();
        return;
    case EventType::EVNT_CTRL_T_STR_PRS_LNG:
        state->str_prs_lng();
        return;
    case EventType::EVNT_CTRL_T_STP_PRS_SRT:
        state->stp_prs_srt();
        return;
    case EventType::EVNT_CTRL_T_RST_PRS_SRT:
        state->rst_prs_srt();
        return;
    case EventType::EVNT_SEN_ESTOP_ON:
        state->estop_on();
        return;
    case EventType::EVNT_ERR:
        state->err();
        return;
    case EventType::EVNT_ERR_GONE:
        state->all_err_gone();
        return;
    case EventType::EVNT_SRV_DONE:
        state->srv_done();
        return;
    default:
        return;
    }
}
}
}
}
