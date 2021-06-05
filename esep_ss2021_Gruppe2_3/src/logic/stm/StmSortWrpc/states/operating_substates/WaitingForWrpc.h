#pragma once
#include "../../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

class WaitingForWrpc: public SortWrpcBaseState {
public:
    STATE_HEADER_INIT

protected:
    void entry() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
