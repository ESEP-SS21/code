#pragma once

#include "wp_transfer_base_state.h"

namespace logic {
namespace stm {
namespace StmWpTransfer {

class Waiting: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool lb_en_blck() override;
};

class notBlocked: public WpTransferBaseState {
public:

};

class Blocked: public WpTransferBaseState {
public:
};

class WaitingForWpToLeave: public WpTransferBaseState {
public:
    bool lb_en_clr() override;
};


} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
