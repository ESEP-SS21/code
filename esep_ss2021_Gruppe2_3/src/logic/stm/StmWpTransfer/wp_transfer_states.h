#pragma once

#include "wp_transfer_base_state.h"

namespace logic {
namespace stm {
namespace StmWpTransfer {

class Waiting: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool lb_en_blck() override;
    void reset_to_start() override;
};

class NotBlocked: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool tim_alrt(int tim_id) override;
    bool ack() override;
    void entry() override;
    void reset_to_start() override;
};

class Blocked: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool ack() override;
    void reset_to_start() override;
    void entry() override;

};

class WaitingForWpToLeave: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool lb_en_clr() override;
    void reset_to_start() override;
};

class WaitingForFinTransfer: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool tim_alrt(int tim_id) override;
    void entry() override;
    void reset_to_start() override;
};


} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
