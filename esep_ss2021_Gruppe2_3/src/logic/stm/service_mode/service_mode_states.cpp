#include "service_mode_states.h"
#include "dispatcher/color.h"

namespace logic {
namespace stm {
namespace stm_service_mode {

using namespace dispatcher;

STATE_INIT(StartState)

bool StartState::handle(const Event &event) {
    if (event.type == EventType::EVNT_SRV_STR) {
        exit();
        switch_state<Calibrate>();
        entry();
        return true;
    }
    return false;
}

void StartState::entry() {
    _waiting_for_ack = false;
    _currSensType = SensorEnum::lb_st;
}

STATE_INIT(Calibrate)

void Calibrate::entry() {
    _eventSender->send({EventType::EVNT_SEN_HEIGHT_REQ});
}

bool Calibrate::handle(const Event &event) {
    if (event.type == EventType::EVNT_SEN_HEIGHT_HE) {
        _eventSender->send({EventType::EVNT_SEN_HEIGHT_REQ, event.payload});
        exit();
        switch_state<Leds>();
        entry();
        return true;
    }
    return false;
}

STATE_INIT(Leds)

bool Leds::handle(const Event &event) {
    if (_waiting_for_ack && event.type == EventType::EVNT_CTRL_T_RST_PRS_SRT) {
        handle_rst();
        exit();
        switch_state<Stoplight>();
        entry();
        return true;
    }
    return false;
}

void Leds::entry() {
    step_done();
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_STR_LED_ON});
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_ON});
}

void Leds::exit() {
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_STR_LED_OFF});
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_OFF});
}


STATE_INIT(Stoplight)

bool Stoplight::handle(const Event &event) {
    if (_waiting_for_ack && event.type == EventType::EVNT_CTRL_T_RST_PRS_SRT) {
        handle_rst();
        exit();
        switch_state<BeltFwd>();
        entry();
        return true;
    }
    return false;
}

void Stoplight::entry() {
    _eventSender->send({EventType::EVNT_ACT_STPL_LED_ON, Color::ALL});
    step_done();
}

void Stoplight::exit() {
    _eventSender->send({EventType::EVNT_ACT_STPL_LED_BLNK_SLW, Color::GREEN});
}

STATE_INIT(BeltFwd)

bool BeltFwd::handle(const Event &event) {
    if (_waiting_for_ack && event.type == EventType::EVNT_CTRL_T_RST_PRS_SRT) {
        handle_rst();
        exit();
        switch_state<BeltBwd>();
        entry();
        return true;
    }
    return false;
}

void BeltFwd::entry() {
    _eventSender->send({EventType::EVNT_ACT_BELT_FWD});
    step_done();
}

void BeltFwd::exit() {
    _eventSender->send({EventType::EVNT_ACT_BELT_STP});
}

STATE_INIT(BeltBwd)

bool BeltBwd::handle(const Event &event) {
    if (_waiting_for_ack && event.type == EventType::EVNT_CTRL_T_RST_PRS_SRT) {
        handle_rst();
        exit();
        switch_state<SortDisc>();
        entry();
        return true;
    }
    return false;
}

void BeltBwd::entry() {
    _eventSender->send({EventType::EVNT_ACT_BELT_BWD});
    step_done();
}

void BeltBwd::exit() {
    _eventSender->send({EventType::EVNT_ACT_BELT_STP});
}

STATE_INIT(SortDisc)

bool SortDisc::handle(const Event &event) {
    if (_waiting_for_ack && event.type == EventType::EVNT_CTRL_T_RST_PRS_SRT) {
        handle_rst();
        exit();
        switch_state<SortNoDisc>();
        entry();
        return true;
    }

    if (event.type == EventType::EVNT_TIM_ALRT && (TimerID(event.type) == TimerID::SRV_Timer)) {
        _eventSender->send({EventType::EVNT_ACT_SORT_RST});
        step_done();
    }

    return false;
}

void SortDisc::entry() {
    _eventSender->send({EventType::EVNT_ACT_SORT_DSC});
    _eventSender->send(Event::CreateTimer(TimerID::SRV_Timer, 2000));
}

void SortDisc::exit() {
    _eventSender->send({EventType::EVNT_ACT_SORT_RST});
}


STATE_INIT(SortNoDisc)

bool SortNoDisc::handle(const Event &event) {
    if (_waiting_for_ack && event.type == EventType::EVNT_CTRL_T_RST_PRS_SRT) {
        handle_rst();
        exit();
        switch_state<Sensors>();
        entry();
        return true;
    }

    if (event.type == EventType::EVNT_TIM_ALRT && (TimerID(event.type) == TimerID::SRV_Timer)) {
        _eventSender->send({EventType::EVNT_ACT_SORT_RST});
        step_done();
    }

    return false;
}

void SortNoDisc::entry() {
    _eventSender->send({EventType::EVNT_ACT_SORT_NO_DSC});
    _eventSender->send(Event::CreateTimer(TimerID::SRV_Timer, 2000));
}

void SortNoDisc::exit() {
    _eventSender->send({EventType::EVNT_ACT_SORT_RST});
}

STATE_INIT(Sensors)

bool Sensors::handle(const Event &event) {

    if (_waiting_for_ack && event.type == EventType::EVNT_CTRL_T_RST_PRS_SRT) {
        handle_rst();
        if (_currSensType == SensorEnum::DONE) {
            exit();
            switch_state<StartState>();
            entry();
        }
        return true;
    }

    if (_currSensType == SensorEnum::lb_st && event.type == EventType::EVNT_SEN_LB_ST_CLR ||
        _currSensType == SensorEnum::lb_en && event.type == EventType::EVNT_SEN_LB_EN_CLR ||
        _currSensType == SensorEnum::lb_ra && event.type == EventType::EVNT_SEN_LB_RA_CLR ||
        _currSensType == SensorEnum::lb_sw && event.type == EventType::EVNT_SEN_LB_SW_CLR ||
        _currSensType == SensorEnum::me && event.type == EventType::EVNT_SEN_METAL_DTC
        ) {

        _currSensType = SensorEnum(static_cast<int>(_currSensType) + 1);
        step_done();
        return true;
    }

    return false;
}


} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
