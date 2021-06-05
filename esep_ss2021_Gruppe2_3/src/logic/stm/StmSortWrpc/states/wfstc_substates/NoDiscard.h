#pragma once
#include "../../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

class NoDiscard: public SortWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool lb_sw_clr() override;

protected:
    void entry() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
