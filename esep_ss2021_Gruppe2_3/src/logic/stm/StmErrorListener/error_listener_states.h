#pragma once

#include "error_listener_base_state.h"

namespace logic {
namespace stm {
namespace StmErrorListener {

class WaitingForError: public ErrorListenerBaseState {
public:
    STATE_HEADER_INIT
    bool err(int payload) override;
    void entry() override;
};

class WaitingForResolve: public ErrorListenerBaseState {
public:
    STATE_HEADER_INIT
    bool lb_ra_clr() override;
    bool estop_on() override;
};

} /* namespace StmErrorListener */
} /* namespace stm */
} /* namespace logic */
