#pragma once
#include "../recieve_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

class Running: public RecieveWrpcBaseState {
public:
    SUBSTM_HEADER_INIT
    bool err() override;
    bool estop_on() override;
    bool stp_prs_srt() override;
    bool lb_st_blck() override;
    bool belt_stp() override;
    bool belt_fwd() override;
protected:
    void entry_sub_start_node() override;
    void entry_history() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

