#pragma once
#include "../recieve_wrpc_base_state.h"
namespace logic {
namespace stm {
namespace recieveWrpcStm {

class Service: public RecieveWrpcBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool srv_done() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

