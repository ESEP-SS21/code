#pragma once
#include "top_level_base_state.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

template<typename StartState>
class Idle : public TopLevelBaseState<StartState> {
public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool str_prs_srt() override;
    bool str_prs_lng() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

