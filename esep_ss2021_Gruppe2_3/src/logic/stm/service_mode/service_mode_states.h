#pragma once

#include "service_mode_base_state.h"

namespace logic {
namespace stm {
namespace stm_service_mode {

class StartState: public ServiceModeBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;

    void entry() override;
};

class Calibrate: public ServiceModeBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
    void entry() override;
};

class Sensors: public ServiceModeBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
};

class Leds: public ServiceModeBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
    void entry() override;
    void exit() override;
};

class Stoplight: public ServiceModeBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
    void entry() override;
    void exit() override;
};

class BeltFwd: public ServiceModeBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
    void entry() override;
    void exit() override;
};

class BeltBwd: public ServiceModeBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
    void entry() override;
    void exit() override;
};

class SortDisc: public ServiceModeBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
    void entry() override;
    void exit() override;
};

class SortNoDisc: public ServiceModeBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
    void entry() override;
    void exit() override;
};

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
