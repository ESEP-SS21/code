#pragma once

#include <logic/stm/StmRecieveWrpc/recieve_wrpc_base_state.h>

namespace logic {
namespace stm {
namespace top_level {

template<typename StartState>
class Running: public TopLevelBaseState<StartState> {
public:
    SUBSTM_HEADER_INIT
    bool err() override;
    bool estop_on() override;
    bool stp_prs_srt() override;
    bool lb_st_blck() override;
    bool belt_stp() override;
    bool belt_fwd() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

