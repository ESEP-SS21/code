#pragma once

#include <logic/stm/base_context.h>
#include "top_level_base_state.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

template<typename SubstateRunningStart>
class Error: public TopLevelBaseState<SubstateRunningStart> {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool all_err_gone() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

