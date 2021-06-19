#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace stm_service_mode {

class ServiceModeBaseState : public BaseBaseState {
public:
    void entry() override {};

    void exit() override {};

    void end_service() {
        _eventSender->send({EventType::EVNT_SRV_DONE, 0, true});
//        new(this) ServiceModeState();
    }

protected:
    enum class SensorEnum {
        lb_st,
        lb_en,
        lb_sw,
        lb_ra,
        me,
        DONE,
    };

    bool _waiting_for_ack;
    SensorEnum _currSensType = SensorEnum::lb_st;

    void step_done() {
        _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_ON});
        _waiting_for_ack = true;
    }

    void handle_rst() {
        _waiting_for_ack = false;
        _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_OFF});
    }

};

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
