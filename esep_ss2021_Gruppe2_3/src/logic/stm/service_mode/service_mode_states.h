#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace ServiceModeStm {

enum class Step {
    calibrate_he_req,
    calibrate_he_he,
    sen_lb_st,
    sen_lb_en,
    sen_lb_sw,
    sen_lb_ra,
    sen_me,
    DONE,
};

class ServiceModeState : public BaseBaseState {
private:
    Step _currStep;
    bool waiting_for_ack;

    void end_service();

    void step_done();

public:
    ServiceModeState() = default;

    STATE_HEADER_INIT

    bool handle(const Event &event) override;

    void handle_ack();

    void exit() override{
        end_service();
    }
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
