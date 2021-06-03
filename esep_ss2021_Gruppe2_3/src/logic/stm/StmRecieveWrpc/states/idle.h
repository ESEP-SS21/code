#pragma once
#include "../recieve_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

class Idle : public RecieveWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool str_prs_srt() override;
    bool str_prs_lng() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

