#pragma once
#include "../recieve_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

class Error: public RecieveWrpcBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool all_err_gone() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

