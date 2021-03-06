/*
 * TestInterruptListener.cpp
 *
 *  Created on: 12.05.2021
 *      Author: jendr
 */

#include <hal/HalManagerSen.h>

namespace hal {

HalManagerSen::HalManagerSen(const std::string& dispatcher_name, bool playback_mode) :
        DispatcherClient(dispatcher_name, "HAL Manager Sen") {
    _pb_mode = playback_mode;
    _running = true;
    _gpio = std::make_shared<GPIOWrapper>();
    _hal = std::unique_ptr<HAL>(new HAL(_gpio));
    _irq_rec_channel = std::unique_ptr<dispatcher::cnnMngmnt::QnxChannel>(
            new dispatcher::cnnMngmnt::QnxChannel());
    _irq_connection = std::unique_ptr<dispatcher::cnnMngmnt::QnxConnection>(
            new dispatcher::cnnMngmnt::QnxConnection(_irq_rec_channel->get_chid()));
    subscribe(dispatcher::EventType::EVNT_SEN_HEIGHT_REQ);
    _listener_thread = std::thread([this] {this->int_rec_fnct();});
    _start_pressed_time = std::chrono::high_resolution_clock::now();
    _stop_pressed_time = std::chrono::high_resolution_clock::now();
    _reset_pressed_time = std::chrono::high_resolution_clock::now();
}

void HalManagerSen::handle(Event &event){
    if(_pb_mode){
        return;
    }
    if (event.type == dispatcher::EventType::EVNT_SEN_HEIGHT_REQ) {
        if (event.payload == 0) {
            _hal->get_height_sensor().get()->sample();
        } else {
            _hal->get_height_sensor().get()->set_zero_point(event.payload);
        }

    }
}

void HalManagerSen::int_rec_fnct() {
    struct sigevent _input_event;
    struct sigevent _adc_event;
    // creates a pulse message which is sent when the event occurs
    SIGEV_PULSE_INIT(&_input_event, _irq_connection->get_id(), SIGEV_PULSE_PRIO_INHERIT,
            PULSE_GPIO_IRQ, 0);
    SIGEV_PULSE_INIT(&_adc_event, _irq_connection->get_id(), SIGEV_PULSE_PRIO_INHERIT,
            PULSE_ADC_IRQ, 0);
    // configure our thread
    ThreadCtl( _NTO_TCTL_IO, 0);
    // attach our created event to an interrupt
    int intIdGPIO = InterruptAttachEvent(GPIO_IRQ_NR, &_input_event, _NTO_INTR_FLAGS_TRK_MSK);
    if (intIdGPIO == -1) {
        perror("fail");
        _logger->error("Attaching Event to Interrupt failed");
        exit(1);
    }
    int intIdADC = InterruptAttachEvent(ADC_IRQ_NR, &_adc_event, _NTO_INTR_FLAGS_TRK_MSK);
    if (intIdADC == -1) {
        perror("fail");
        _logger->error("Attaching Event to Interrupt failed");
        exit(1);
    }
    header_t header;

    while (_running) {
        dispatcher::cnnMngmnt::MsgType msg_type = _irq_rec_channel->msg_receive(&header,
                sizeof(header_t));

        if (msg_type == dispatcher::cnnMngmnt::MsgType::error) {
            _logger->error("IRQ handler received error '{}'", header.type);
            break;
        }

        if (msg_type == dispatcher::cnnMngmnt::MsgType::puls) {
            if (header.code == _PULSE_CODE_UNBLOCK) {
                continue;
            }
            if (header.code == PULSE_GPIO_IRQ) {
                _gpio->reset_interrupt();
                InterruptUnmask(GPIO_IRQ_NR, intIdGPIO);
                send_event_to_dispatcher();
                continue;
            }
            if (header.code == PULSE_ADC_IRQ) {
                _hal->get_height_sensor().get()->reset_interrupt();
                InterruptUnmask(ADC_IRQ_NR, intIdADC);
                int height_raw = _hal->get_height_sensor().get()->get_value();
                float mm = _hal->get_height_sensor().get()->convert_to_mm(height_raw);
                dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_HEIGHT_HE,
                        static_cast<int>(mm), false };
                send(e, 20);
                continue;
            }

        }

        //else sync msg

        if ((_IO_BASE <= header.type) && (header.type <= _IO_MAX)) {
            // Some QNX IO msg generated by gns was received
            handle_qnx_io_msg(header);
            continue;
        }
        // TODO handling for unsupported sync message
    }
}

void HalManagerSen::send_event_to_dispatcher() {
    if (_hal->get_metal_sensor().get()->was_metal() && !_pb_mode) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_METAL_DTC, 0, false };
        send(e, 20);
    }

    if (_hal->get_estop().get()->was_pressed()) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_ESTOP_ON, 0, true };
        send(e, 40);
    }
    if (_hal->get_estop().get()->was_released()) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_ESTOP_OFF, 0, true };
        send(e, 40);
    }
    if (_pb_mode){
        return;
    }
    if (_hal->get_cp_buttons().get()->was_pressed(hal::CPSTART)) {
        _start_pressed_time = std::chrono::high_resolution_clock::now();
    }
    if (_hal->get_cp_buttons().get()->was_released(hal::CPSTART)) {
        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - _start_pressed_time).count();
        if (delta > 3000) {
            dispatcher::Event e = { dispatcher::EventType::EVNT_CTRL_T_STR_PRS_LNG, 0, true };
            send(e, 20);
        }
        if (delta < 500){
            dispatcher::Event e = { dispatcher::EventType::EVNT_CTRL_T_STR_PRS_SRT, 0, true };
            send(e, 20);
        }
    }
    if (_hal->get_cp_buttons().get()->was_pressed(hal::CPSTOP)) {
        _stop_pressed_time = std::chrono::high_resolution_clock::now();
    }
    if (_hal->get_cp_buttons().get()->was_released(hal::CPSTOP)) {
        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - _stop_pressed_time).count();
        if (delta > 3000) {
            dispatcher::Event e = { dispatcher::EventType::EVNT_CTRL_T_STP_PRS_LNG, 0, true };
            send(e, 20);
        }
        if (delta < 500) {
            dispatcher::Event e = { dispatcher::EventType::EVNT_CTRL_T_STP_PRS_SRT, 0, true };
            send(e, 20);
        }
    }
    if (_hal->get_cp_buttons().get()->was_pressed(hal::CPRESET)) {
        _reset_pressed_time = std::chrono::high_resolution_clock::now();
    }
    if (_hal->get_cp_buttons().get()->was_released(hal::CPRESET)) {
        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - _reset_pressed_time).count();
        if (delta > 3000) {
            dispatcher::Event e = { dispatcher::EventType::EVNT_CTRL_T_RST_PRS_LNG, 0, true };
            send(e, 20);
        }
        if (delta < 500) {
            dispatcher::Event e = { dispatcher::EventType::EVNT_CTRL_T_RST_PRS_SRT, 0, true };
            send(e, 20);
        }
    }

    if (_hal->get_light_barriers().get()->was_blocked(hal::LBSTART)) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_LB_ST_BLCK, 0, false };
        send(e, 20);
    }
    if (_hal->get_light_barriers().get()->was_cleared(hal::LBSTART)) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_LB_ST_CLR, 0, false };
        send(e, 20);
    }
    if (_hal->get_light_barriers().get()->was_blocked(hal::LBHEIGHT)) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_LB_HE_BLCK, 0, false };
        send(e, 20);
    }
    if (_hal->get_light_barriers().get()->was_cleared(hal::LBHEIGHT)) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_LB_HE_CLR, 0, false };
        send(e, 20);
    }
    if (_hal->get_light_barriers().get()->was_blocked(hal::LBSWITCH)) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_LB_SW_BLCK, 0, false };
        send(e, 20);
    }
    if (_hal->get_light_barriers().get()->was_cleared(hal::LBSWITCH)) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_LB_SW_CLR, 0, false };
        send(e, 20);
    }
    if (_hal->get_light_barriers().get()->was_blocked(hal::LBRAMP)) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_LB_RA_BLCK, 0, false };
        send(e, 20);
    }
    if (_hal->get_light_barriers().get()->was_cleared(hal::LBRAMP)) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_LB_RA_CLR, 0, false };
        send(e, 20);
    }
    if (_hal->get_light_barriers().get()->was_blocked(hal::LBEND)) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_LB_EN_BLCK, 0, false };
        send(e, 20);
    }
    if (_hal->get_light_barriers().get()->was_cleared(hal::LBEND)) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_LB_EN_CLR, 0, false };
        send(e, 20);
    }

}

void HalManagerSen::handle_qnx_io_msg(header_t header) {
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

HalManagerSen::~HalManagerSen() {
    _running = false;
    dispatcher::cnnMngmnt::QnxConnection(_irq_rec_channel->get_chid()).msg_send_pulse(1,
    _PULSE_CODE_UNBLOCK, 0);
    _listener_thread.join();
}

} /* namespace hal */
