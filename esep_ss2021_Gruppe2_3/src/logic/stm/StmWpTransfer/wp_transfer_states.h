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

class NotBlocked: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool tim_alrt(int tim_id) override;
    bool ack() override;
    void entry() override;
};

class Blocked: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool ack() override;

protected:
    void entry() override;
    void entry_history() override;
    void reset_to_start() override;
};

class WaitingForWpToLeave: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool lb_en_clr() override;
    bool tim_alrt(int tim_id) override;
    void entry() override;
private:
    bool warning = false;
};

class WaitingForFinTransfer: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool tim_alrt(int tim_id) override;
    void entry() override;
};


} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
