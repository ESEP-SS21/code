#pragma once
#include "../../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

class WaitingForWrpc: public SortWrpcBaseState {
public:
    STATE_HEADER_INIT

protected:
    bool has_super_exit_with_lb_sw_blck_from_waiting_for_wrpc() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
