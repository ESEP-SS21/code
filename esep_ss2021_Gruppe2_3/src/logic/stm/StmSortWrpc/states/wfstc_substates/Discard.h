#pragma once
#include "../../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

static constexpr int SW_CLR_TIME_TOLERANCE_MS = 2300;

class Discard: public SortWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool tim_alrt(int tim_id) override;

    bool has_super_exit_with_lb_sw_clr() override;

protected:
    void entry() override;

};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
