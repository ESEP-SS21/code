#include "recieve_wrpc_context.h"
#include "recieve_wrpc_base_state.h"
#include "states/idle.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

CONTEXT_CTOR(RecieveWrpcContext)

using namespace dispatcher;

void RecieveWrpcContext::handle(Event e) {
    auto *state = (RecieveWrpcBaseState *) (_state);

    switch (e.type) {
        case EventType::EVNT_SEN_LB_ST_BLCK:
            state->lb_st_blck();
            return;
        case EventType::EVNT_ACT_BELT_STP:
            state->belt_stp();
            return;
        case EventType::EVNT_ACT_BELT_FWD:
            state->belt_fwd();
            return;
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
        default:
            state->srv_done();
            return;
    }

}

}
}
}
