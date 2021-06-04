#pragma once
#include "../../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

class WaitingForRampToClear: public SortWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool tim_alrt(int payload) override;
    bool lb_ra_clr() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
