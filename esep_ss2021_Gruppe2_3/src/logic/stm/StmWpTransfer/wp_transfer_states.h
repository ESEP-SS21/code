#pragma once

#include "wp_transfer_base_state.h"

namespace logic {
namespace stm {
namespace StmWpTransfer {

class Waiting: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool lb_en_blck();
    bool wrpc_trans_req() override;
};

class NotBlocked: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool tim_alrt(int tim_id) override;
    bool ack();
};

class Blocked: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool ack();

protected:
    void entry() override;
    void entry_history() override;
    void reset_to_start() override;
};

class WaitingForWpToLeave: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool lb_en_clr();
    bool tim_alrt(int tim_id);
private:
    bool warning = false;
};

class WaitingForFinTransfer: public WpTransferBaseState {
public:
    STATE_HEADER_INIT
    bool belt_stp();
    bool tim_alrt(int tim_id);
};


} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
