#include <logic/stm/StmSortWrpc/sort_wrpc_base_state.h>
#include <logic/stm/StmSortWrpc/sort_wrpc_context.h>
#include "states/sub_operating.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

//put the start state of your stm here
CONTEXT_CTOR(SortWrpcContext, SubOperating)

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
        default:
            return;
    }

}

}
}
}
