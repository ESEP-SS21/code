#pragma once
#include "top_level_base_state.h"
namespace logic {
namespace stm {
namespace top_level {

template<typename StartState>
class Service: public TopLevelBaseState<StartState> {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool srv_done() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

