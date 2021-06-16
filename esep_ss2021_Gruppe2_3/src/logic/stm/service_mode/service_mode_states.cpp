#include <logic/stm/StmRecieveWrpc/receive_wrpc_states.h>
#include "service_mode_states.h"


namespace logic {
namespace stm {
namespace ServiceModeStm {

using namespace dispatcher;

STATE_INIT(ServiceModeState)

bool ServiceModeStm::ServiceModeState::handle(const Event &event) {
    if (waiting_for_ack) {
        if (event.type == EventType::EVNT_CTRL_T_RST_PRS_SRT)
            handle_ack();
        return true;
    }

    switch (_currStep) {
        case Step::calibrate_he_req:
            _eventSender->send({EventType::EVNT_SEN_HEIGHT_REQ});
            return true;
        case Step::calibrate_he_he:
            if (event.type == EventType::EVNT_SEN_HEIGHT_HE)
                _eventSender->send({EventType::EVNT_SEN_HEIGHT_REQ, event.payload});
            return true;
        case Step::sen_lb_st:
            if (event.type == EventType::EVNT_SEN_LB_ST_CLR)
                step_done();
            return true;
        case Step::sen_lb_en:
            if (event.type == EventType::EVNT_SEN_LB_EN_CLR)
                step_done();
            return true;
        case Step::sen_lb_ra:
            if (event.type == EventType::EVNT_SEN_LB_RA_CLR)
                step_done();
            return true;
        case Step::sen_lb_sw:
            if (event.type == EventType::EVNT_SEN_LB_SW_CLR)
                step_done();
            return true;
        case Step::sen_me:
            if (event.type == EventType::EVNT_SEN_METAL_DTC)
                step_done();
            return true;

        case Step::DONE:
            _logger->error("");
    }

    return true;
}

void ServiceModeState::handle_ack() {
    waiting_for_ack = false;
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_OFF});
    _currStep = Step(static_cast<int>(_currStep) + 1);
    if (_currStep == Step::DONE)
        end_service();
}

void ServiceModeState::end_service() {
    _eventSender->send({EventType::EVNT_SRV_DONE, 0, true});
    // clear state data
    new(this) ServiceModeState();
}

void ServiceModeState::step_done() {
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_ON});
    waiting_for_ack = true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
