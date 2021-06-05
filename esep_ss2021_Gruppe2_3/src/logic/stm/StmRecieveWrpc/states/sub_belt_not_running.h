#pragma once
#include "../recieve_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

class BeltNotRunning: public RecieveWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool lb_st_blck() override;
    bool belt_fwd() override;
protected:
    void entry() override;
    void entry_history() override;
    void reset_to_start() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
