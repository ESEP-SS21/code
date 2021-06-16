#pragma once

#include <dispatcher/color.h>
#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace ServiceModeStm {

enum class Step {
    calibrate_he_req,
    calibrate_he_he,
    act_led,
    act_stp_light,
    act_belt_fwd,
    act_belt_backw,
    act_sort_dsc,
    act_sort_no_dsc,
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
    bool _waiting_for_ack;
    dispatcher::Color _blink_color;
    std::queue<Event> _reset_events = std::queue<Event>();

    void end_service();
    void step_done();

public:
    ServiceModeState() = default;

    STATE_HEADER_INIT

    bool handle(const Event &event) override;

    void handle_rst();

    void exit() override{
        end_service();
    }

    void blink_stoplight();

    void handle_timers();
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
