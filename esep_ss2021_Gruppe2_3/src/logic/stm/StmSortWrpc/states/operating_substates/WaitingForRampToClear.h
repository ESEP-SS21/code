#pragma once
#include "../../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

static constexpr int RA_CLR_TIME_TOLERANCE_MS = 200;

class WaitingForRampToClear: public SortWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool tim_alrt(int tim_id) override;
    bool lb_ra_clr() override;
    void entry() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
