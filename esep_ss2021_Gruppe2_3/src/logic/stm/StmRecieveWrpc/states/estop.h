#pragma once
#include "../recieve_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

class EStop: public RecieveWrpcBaseState {

public:
    STATE_HEADER_INIT
    bool rst_prs_srt() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
