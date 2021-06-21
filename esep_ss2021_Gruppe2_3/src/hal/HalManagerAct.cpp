/*
 * TestInterruptListener.cpp
 *
 *  Created on: 12.05.2021
 *      Author: jendr
 */

#include <hal/HalManagerAct.h>

namespace hal {

HalManagerAct::HalManagerAct(const std::string& dispatcher_name) :
        DispatcherClient(dispatcher_name, "HAL Manager Act") {
    _irq_rec_channel = nullptr;
    _running = true;
    _gpio = std::make_shared<GPIOWrapper>();
    _hal = std::unique_ptr<HAL>(new HAL(_gpio));
    _irq_rec_channel = std::unique_ptr<dispatcher::cnnMngmnt::QnxChannel>(
            new dispatcher::cnnMngmnt::QnxChannel());
    _irq_connection = std::unique_ptr<dispatcher::cnnMngmnt::QnxConnection>(
            new dispatcher::cnnMngmnt::QnxConnection(_irq_rec_channel->get_chid()));

    subscribe( { dispatcher::EventType::EVNT_ACT_CTRL_T_STR_LED_ON,
            dispatcher::EventType::EVNT_ACT_CTRL_T_STR_LED_OFF,
            dispatcher::EventType::EVNT_ACT_CTRL_T_RST_LED_ON,
            dispatcher::EventType::EVNT_ACT_CTRL_T_RST_LED_OFF,
            dispatcher::EventType::EVNT_ACT_CTRL_Q1_LED_ON,
            dispatcher::EventType::EVNT_ACT_CTRL_Q1_LED_OFF,
            dispatcher::EventType::EVNT_ACT_CTRL_Q2_LED_ON,
            dispatcher::EventType::EVNT_ACT_CTRL_Q2_LED_OFF,
            dispatcher::EventType::EVNT_ACT_BELT_BWD, dispatcher::EventType::EVNT_ACT_BELT_FWD,
            dispatcher::EventType::EVNT_ACT_BELT_STP, dispatcher::EventType::EVNT_ACT_SORT_DSC,
            dispatcher::EventType::EVNT_ACT_SORT_NO_DSC, dispatcher::EventType::EVNT_ACT_SORT_RST,
            dispatcher::EventType::EVNT_ACT_STPL_LED_ON,
            dispatcher::EventType::EVNT_ACT_STPL_LED_OFF,
            dispatcher::EventType::EVNT_ACT_STPL_LED_BLNK_FST,
            dispatcher::EventType::EVNT_ACT_STPL_LED_BLNK_SLW,});
}

void HalManagerAct::handle(dispatcher::Event& event) {
    if (event.type == dispatcher::EventType::EVNT_ACT_BELT_BWD) {
        _hal->get_cb_motor().get()->set_direction(Direction::FAST_BACKWARDS);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_BELT_FWD) {
        _hal->get_cb_motor().get()->set_direction(Direction::FAST_FORWARDS);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_BELT_STP) {
        _hal->get_cb_motor().get()->set_direction(Direction::STOP);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_SORT_DSC) {
        _hal->get_sorting_mechanism().get()->discard();
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_SORT_NO_DSC) {
        _hal->get_sorting_mechanism().get()->do_not_discard();
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_SORT_RST) {
        _hal->get_sorting_mechanism().get()->reset();
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_CTRL_T_STR_LED_ON) {
        _hal->get_leds().get()->enable(LED_type::START);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_CTRL_T_STR_LED_OFF) {
        _hal->get_leds().get()->disable(LED_type::START);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_CTRL_T_RST_LED_ON) {
        _hal->get_leds().get()->enable(LED_type::RESET);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_CTRL_T_RST_LED_OFF) {
        _hal->get_leds().get()->disable(LED_type::RESET);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_CTRL_Q1_LED_ON) {
            _hal->get_leds().get()->enable(LED_type::Q1);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_CTRL_Q1_LED_OFF) {
        _hal->get_leds().get()->disable(LED_type::Q1);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_CTRL_Q2_LED_ON) {
        _hal->get_leds().get()->enable(LED_type::Q2);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_CTRL_Q2_LED_OFF) {
        _hal->get_leds().get()->disable(LED_type::Q2);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_STPL_LED_ON) {
        _hal->get_stoplight().get()->enable(Color(event.payload));
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_STPL_LED_OFF) {
        _hal->get_stoplight().get()->disable(Color(event.payload));
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_STPL_LED_BLNK_FST) {
        _hal->get_stoplight().get()->blink(Color(event.payload), Speed::FAST);
    }
    if (event.type == dispatcher::EventType::EVNT_ACT_STPL_LED_BLNK_SLW) {
        _hal->get_stoplight().get()->blink(Color(event.payload), Speed::SLOW);
    }
}

void HalManagerAct::handle_qnx_io_msg(header_t header) {
    if (header.type == _IO_CONNECT) {
        // QNX IO msg _IO_CONNECT was received; answer with EOK
        _irq_rec_channel->msg_reply(EOK);
        _logger->trace("IRQ handler received _IO_CONNECT");
        return;
    }
    // Some other QNX IO message was received; reject it
    _logger->critical("IRQ handler received unexpected (sync.) msg type '{}'", header.type);
    _irq_rec_channel->msg_reply_error(ENOSYS);
}

HalManagerAct::~HalManagerAct() {
    _running = false;
    dispatcher::cnnMngmnt::QnxConnection(_irq_rec_channel->get_chid()).msg_send_pulse(1,
    _PULSE_CODE_UNBLOCK, 0);
}

// Temporary
void HalManagerAct::set_belt_state(bool value) {
    if (value) {
        _hal->get_cb_motor().get()->set_direction(FAST_FORWARDS);
    } else {
        _hal->get_cb_motor().get()->set_direction(STOP);
    }
}
// Temporary
void HalManagerAct::set_junc_state(bool value) {
    if (value) {
        _hal->get_sorting_mechanism()->do_not_discard();
    } else {
        _hal->get_sorting_mechanism()->discard();
    }
}

} /* namespace hal */
