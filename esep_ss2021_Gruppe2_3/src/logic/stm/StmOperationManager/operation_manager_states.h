#pragma once

#include "operation_manager_base_state.h"

namespace logic {
namespace stm {
namespace operationManagerStm {

class Running: public OperationManagerBaseState {
public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool conn_lost() override;
    bool err() override;
    bool stp_prs_srt() override;
    bool wrn() override;
    bool wrn_gone() override;
    void entry() override;
    void exit() override;
};

class Idle : public OperationManagerBaseState {
public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool conn_lost() override;
    bool str_prs_srt() override;
    bool str_prs_lng() override;
    void entry() override;
    void exit() override;
};

class EStop: public OperationManagerBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool estop_off() override;
    bool conn_lost() override;
    bool rst_prs_srt() override;
    void entry() override;
    void exit() override;
};

class PendingUnacknowledged: public OperationManagerBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool conn_lost() override;
    bool rst_prs_srt() override;
    bool err_gone() override;
    void entry() override;
};

class PendingAcknowledged: public OperationManagerBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool conn_lost() override;
    bool err_gone() override;
    void entry() override;
};

class GoneUnacknowledged: public OperationManagerBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool conn_lost() override;
    bool str_prs_srt() override;
    void entry() override;
};

class OK: public OperationManagerBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool conn_lost() override;
    bool rst_prs_srt() override;
    void entry() override;
    void exit() override;
};

class Service: public OperationManagerBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool conn_lost() override;
    bool srv_done() override;
    void entry() override;
};
}
}
}
