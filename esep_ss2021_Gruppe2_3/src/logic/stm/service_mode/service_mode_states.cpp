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
    _ackCount = 0;
}

void StartState::exit() {
    _logger->info("Starting service mode. Hold stop button for 3 seconds to abort. Confirm each step with the reset button.");
}

STATE_INIT(Calibrate)

void Calibrate::entry() {
    _eventSender->send({EventType::EVNT_SEN_HEIGHT_REQ});
}

bool Calibrate::handle(const Event &event) {
    if (event.type == EventType::EVNT_SEN_HEIGHT_HE) {
        _eventSender->send({EventType::EVNT_SEN_HEIGHT_REQ, event.payload});
        exit();
        _logger->info("Calibrated height sensor to {}", event.payload);
        switch_state<Leds>();
        entry();
        return true;
    }
    return false;
}

STATE_INIT(Leds)

bool Leds::handle(const Event &event) {
    return switch_to_if_ack<Stoplight>(event);
}

void Leds::entry() {
    step_done();
    _logger->info("Confirm that both start and reset button LEDs are turned on on both systems");
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_STR_LED_ON});
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_ON});
}

void Leds::exit() {
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_STR_LED_OFF});
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_OFF});
}


STATE_INIT(Stoplight)

bool Stoplight::handle(const Event &event) {
    return switch_to_if_ack<BeltFwd>(event);
}

void Stoplight::entry() {
    _logger->info("Confirm that all stoplight LEDs are turned on on both systems");
    _eventSender->send({EventType::EVNT_ACT_STPL_LED_ON, Color::ALL});
    step_done();
}

void Stoplight::exit() {
    _eventSender->send({EventType::EVNT_ACT_STPL_LED_BLNK_SLW, Color::GREEN});
}

STATE_INIT(BeltFwd)

bool BeltFwd::handle(const Event &event) {
    return switch_to_if_ack<BeltBwd>(event);
}

void BeltFwd::entry() {
    _logger->info("Confirm that belts are moving forwards on both systems");
    _eventSender->send({EventType::EVNT_ACT_BELT_FWD});
    step_done();
}

void BeltFwd::exit() {
    _eventSender->send({EventType::EVNT_ACT_BELT_STP});
}

STATE_INIT(BeltBwd)

bool BeltBwd::handle(const Event &event) {
    return switch_to_if_ack<SortDisc>(event);
}

void BeltBwd::entry() {
    _logger->info("Confirm that belts are moving backwards on both systems");
    _eventSender->send({EventType::EVNT_ACT_BELT_BWD});
    step_done();
}

void BeltBwd::exit() {
    _eventSender->send({EventType::EVNT_ACT_BELT_STP});
}

STATE_INIT(SortDisc)

bool SortDisc::handle(const Event &event) {
    if (switch_to_if_ack<SortNoDisc>(event))
        return true;

    if (event.type == EventType::EVNT_TIM_ALRT && (TimerID(event.payload) == TimerID::SRV_Timer)) {
        _eventSender->send({EventType::EVNT_ACT_SORT_RST});
        step_done();
    }

    return false;
}

void SortDisc::entry() {
    _logger->info("Confirm that sorters are in discard position for approx. 2 seconds on both systems");
    _eventSender->send({EventType::EVNT_ACT_SORT_DSC});
    _eventSender->send(Event::CreateTimer(TimerID::SRV_Timer, 2000));
}

void SortDisc::exit() {
    _eventSender->send({EventType::EVNT_ACT_SORT_RST});
}


STATE_INIT(SortNoDisc)

bool SortNoDisc::handle(const Event &event) {
    if (switch_to_if_ack<Sensors>(event))
        return true;

    if (event.type == EventType::EVNT_TIM_ALRT && (TimerID(event.payload) == TimerID::SRV_Timer)) {
        _eventSender->send({EventType::EVNT_ACT_SORT_RST});
        step_done();
    }

    return false;
}

void SortNoDisc::entry() {
    _logger->info("Confirm that sorters are in no discard position for approx. 2 seconds on both systems");
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
        } else {
            log_current_instruction();
        }
        return true;
    }

    if (_currSensType == SensorEnum::lb_st && event.type == EventType::EVNT_SEN_LB_ST_CLR ||
        _currSensType == SensorEnum::lb_en && event.type == EventType::EVNT_SEN_LB_EN_CLR ||
        _currSensType == SensorEnum::lb_sw && event.type == EventType::EVNT_SEN_LB_SW_CLR ||
        _currSensType == SensorEnum::lb_ra && event.type == EventType::EVNT_SEN_LB_RA_CLR ||
        _currSensType == SensorEnum::me && event.type == EventType::EVNT_SEN_METAL_DTC
        ) {

        _eventSender->send({EventType::EVNT_ACK, 0, true});
        return true;
    }

    if (event.type == EventType::EVNT_ACK) {
        _ackCount++;
        _logger->info("{} sensor confirmed working", _ackCount);

        if (_ackCount == 2){
            _currSensType = SensorEnum(static_cast<int>(_currSensType) + 1);
            _ackCount = 0;
            _logger->info("Press reset to confirm");
            step_done();
        }
        return true;
    }

    return false;
}

void Sensors::entry() {
    _logger->info(
        "Test sensors by placing and removing a metal workpiece in the specified sensor on both systems");
    log_current_instruction();
}

void Sensors::log_current_instruction() {
    _logger->info("Place workpiece in {}", _currSensType == SensorEnum::lb_st ? "lightbarrier start" :
                                           _currSensType == SensorEnum::lb_en ? "lightbarrier end" :
                                           _currSensType == SensorEnum::lb_sw ? "lightbarrier switch" :
                                           _currSensType == SensorEnum::lb_ra ? "lightbarrier ramp" :
                                           _currSensType == SensorEnum::me ? "metal sensor" : "error");
}


} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
