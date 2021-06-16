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
        case Step::s1_lb_st:
            if (event.type == EventType::EVNT_SEN_LB_ST_CLR)
                step_done();


        case Step::first:
            break;
        case Step::DONE:
            _logger->error("");
    }
    return true;
}

void ServiceModeState::handle_ack() {
    waiting_for_ack = false;
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_OFF});
    _currStep = Step(static_cast<int>(_currStep) + 1);
    CheckForEndOfService();
}

void ServiceModeState::CheckForEndOfService() {
    if (_currStep == Step::DONE) {
        _eventSender->send({EventType::EVNT_SRV_DONE, 0, true});
        // clear state data
        new(this) ServiceModeState();
    }
}

void ServiceModeState::step_done() {
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_ON});
    waiting_for_ack = true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
