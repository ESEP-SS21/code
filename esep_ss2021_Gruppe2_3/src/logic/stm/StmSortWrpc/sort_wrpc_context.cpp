#include <logic/stm/StmSortWrpc/sort_wrpc_base_state.h>
#include <logic/stm/StmSortWrpc/sort_wrpc_context.h>
#include "states/top_level.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

//put the start state of your stm here
CONTEXT_CTOR(SortWrpcContext, Idle)

using namespace dispatcher;

void SortWrpcContext::handle(Event e) {
    auto *state = (SortWrpcBaseState *) (_state);

    switch (e.type) {
        case EventType::EVNT_SEN_LB_SW_BLCK:
            state->lb_sw_blck();
            return;
        case EventType::EVNT_SEN_LB_SW_CLR:
            state->lb_sw_clr();
            return;
        case EventType::EVNT_SEN_LB_RA_CLR:
            state->lb_ra_clr();
            return;
        case EventType::EVNT_TIM_ALRT:
            state->tim_alrt(e.payload);
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
