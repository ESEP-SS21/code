#pragma once
#include "../../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

class RampFull: public SortWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool lb_sw_blck() override;
    bool lb_ra_clr() override;
protected:
    void entry() override;
    void exit() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
