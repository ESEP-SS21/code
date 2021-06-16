#include <logic/stm/StmRecieveWrpc/receive_wrpc_states.h>
#include "service_mode_states.h"
#include "dispatcher/color.h"


namespace logic {
namespace stm {
namespace ServiceModeStm {

using namespace dispatcher;

STATE_INIT(ServiceModeState)

bool ServiceModeStm::ServiceModeState::handle(const Event &event) {
    if (event.type == EventType::EVNT_TIM_ALRT && (TimerID(event.type) == TimerID::SRV_Timer)) {
        handle_timers();
        return true;
    }

    if (event.type == EventType::EVNT_CTRL_T_RST_PRS_SRT) {
        if (_waiting_for_ack)
            handle_rst();
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
        case Step::act_led:
            _reset_events.emplace<Event>({EventType::EVNT_ACT_CTRL_T_STR_LED_OFF});
            _reset_events.emplace<Event>({EventType::EVNT_ACT_CTRL_T_RST_LED_OFF});
            step_done();
            _eventSender->send({EventType::EVNT_ACT_CTRL_T_STR_LED_ON});
            _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_ON});
            return true;
        case Step::act_stp_light:
            step_done();
            blink_stoplight();
            return true;
        case Step::act_belt_fwd:
            _reset_events.emplace<Event>({EventType::EVNT_ACT_BELT_STP});
            step_done();
            _eventSender->send({EventType::EVNT_ACT_BELT_FWD});
            return true;
        case Step::act_belt_backw:
            _reset_events.emplace<Event>({EventType::EVNT_ACT_BELT_STP});
            step_done();
            _eventSender->send({EventType::EVNT_ACT_BELT_BWD});
            return true;
        case Step::act_sort_dsc:
            _eventSender->send({EventType::EVNT_ACT_SORT_DSC});
            _eventSender->send(Event::CreateTimer(TimerID::SRV_Timer, 2000));
        case Step::act_sort_no_dsc:
            _eventSender->send({EventType::EVNT_ACT_SORT_NO_DSC});
            _eventSender->send(Event::CreateTimer(TimerID::SRV_Timer, 2000));
        default:
            _logger->error("Something unexpected happened");
    }

    return true;
}

void ServiceModeState::handle_timers() {
    if (_currStep == Step::act_stp_light)
        blink_stoplight();
    else if (_currStep == Step::act_sort_dsc ||
             _currStep == Step::act_sort_no_dsc) {
        _eventSender->send({EventType::EVNT_ACT_SORT_RST});
        step_done();
    }
}

void ServiceModeState::blink_stoplight() {
    _eventSender->send(EventType::EVNT_ACT_STPL_LED_BLNK_FST, _blink_color);
    _eventSender->send(Event::CreateTimer(TimerID::SRV_Timer, 250, false));
    _blink_color = _blink_color == Color::RED ? Color::GREEN :
                   _blink_color == Color::GREEN ? Color::YELLOW : Color::RED;
}

void ServiceModeState::handle_rst() {
    _waiting_for_ack = false;
    while (!_reset_events.empty()) {
        auto e = _reset_events.front();
        _reset_events.pop();
        _eventSender->send(e);
    }
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
    _waiting_for_ack = true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
