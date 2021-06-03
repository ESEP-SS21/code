#pragma once
#include "top_level_base_state.h"

namespace logic {
namespace stm {
namespace top_level {

template<typename StartState>
class EStop: public TopLevelBaseState<StartState> {

public:
    STATE_HEADER_INIT
    bool rst_prs_srt() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
