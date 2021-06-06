#pragma once
#include "../../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

class WrpcStuck: public SortWrpcBaseState {
public:
    STATE_HEADER_INIT

    bool has_super_exit_with_lb_sw_clr_from_wrpc_stuck() override;
protected:
    void entry() override;
    void exit() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
