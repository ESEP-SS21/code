#pragma once

#include "operation_manager_base_state.h"

namespace logic {
namespace stm {
namespace operationManagerStm {

class Running: public OperationManagerBaseState {
public:
    STATE_HEADER_INIT
    bool err() override;
    void entry_history() override;
};

class Idle : public OperationManagerBaseState {
public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool str_prs_srt() override;
    bool str_prs_lng() override;
};

class EStop: public OperationManagerBaseState {

public:
    STATE_HEADER_INIT
    bool rst_prs_srt() override;
};

class Error: public OperationManagerBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool err_gone() override;
};

class Service: public OperationManagerBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool srv_done() override;
};
