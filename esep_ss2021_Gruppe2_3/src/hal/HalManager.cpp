/*
 * TestInterruptListener.cpp
 *
 *  Created on: 12.05.2021
 *      Author: jendr
 */

#include <hal/HalManager.h>

namespace hal {

HalManager::HalManager() :
        _irq_rec_channel(nullptr), _is_running(true) {
    _gpio = std::make_shared<GPIOWrapper>();
    _hal = std::unique_ptr<HAL>(new HAL(_gpio));
    _irq_rec_channel = std::unique_ptr<dispatcher::cnnMngmnt::QnxChannel>(
            new dispatcher::cnnMngmnt::QnxChannel());
    _irq_connection = std::unique_ptr<dispatcher::cnnMngmnt::QnxConnection>(
            new dispatcher::cnnMngmnt::QnxConnection(_irq_rec_channel->get_chid()));
    _listener_thread = std::thread([this] {this->int_rec_fnct();});
}

void HalManager::int_rec_fnct() {
    struct sigevent _input_event;
    // creates a pulse message which is sent when the event occurs
    SIGEV_PULSE_INIT(&_input_event, _irq_connection->get_id(), SIGEV_PULSE_PRIO_INHERIT,
            PULSE_GPIO_IRQ, 0);
    // configure our thread
    ThreadCtl( _NTO_TCTL_IO, 0);
    // attach our created event to an interrupt
    int intIdGPIO = InterruptAttachEvent(GPIO_IRQ_NR, &_input_event, _NTO_INTR_FLAGS_TRK_MSK);
    if (intIdGPIO == -1) {
        perror("fail");
        _logger->error("Attaching Event to Interrupt failed");
        exit(1);
    }
    dispatcher::cnnMngmnt::header_t header;

    while (_is_running) {
        dispatcher::cnnMngmnt::MsgType msg_type = _irq_rec_channel->msg_receive(&header,
                sizeof(dispatcher::cnnMngmnt::header_t));

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
            }
            continue;
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

void HalManager::send_event_to_dispatcher(){
    if(_hal->get_estop().get()->was_pressed()){
        _logger->debug("EStop pressed");
    }
    if(_hal->get_estop().get()->was_released()){
        _logger->debug("EStop released");
    }
    if(_hal->get_cp_buttons().get()->was_pressed(hal::CPSTART)){
        _logger->debug("CPButton CPSTART pressed");
    }
    if(_hal->get_cp_buttons().get()->was_released(hal::CPSTART)){
        _logger->debug("CPButton CPSTART released");
    }
    if(_hal->get_cp_buttons().get()->was_pressed(hal::CPSTOP)){
        _logger->debug("CPButton CPSTOP pressed");
    }
    if(_hal->get_cp_buttons().get()->was_released(hal::CPSTOP)){
        _logger->debug("CPButton CPSTOP released");
    }
    if(_hal->get_cp_buttons().get()->was_pressed(hal::CPRESET)){
        _logger->debug("CPButton CPRESET pressed");
    }
    if(_hal->get_cp_buttons().get()->was_released(hal::CPRESET)){
         _logger->debug("CPButton CPRESET released");
    }

    if(_hal->get_light_barriers().get()->was_blocked(hal::LBSTART)){
             _logger->debug("LightBarrier Start was blocked");
    }
    if(_hal->get_light_barriers().get()->was_cleared(hal::LBSTART)){
                 _logger->debug("LightBarrier Start was cleared");
    }
    if(_hal->get_light_barriers().get()->was_blocked(hal::LBHEIGHT)){
             _logger->debug("LightBarrier Height was blocked");
    }
    if(_hal->get_light_barriers().get()->was_cleared(hal::LBHEIGHT)){
                 _logger->debug("LightBarrier Height was cleared");
    }
    if(_hal->get_light_barriers().get()->was_blocked(hal::LBSWITCH)){
             _logger->debug("LightBarrier Switch was blocked");
    }
    if(_hal->get_light_barriers().get()->was_cleared(hal::LBSWITCH)){
                 _logger->debug("LightBarrier Switch was cleared");
    }
    if(_hal->get_light_barriers().get()->was_blocked(hal::LBRAMP)){
             _logger->debug("LightBarrier Ramp was blocked");
    }
    if(_hal->get_light_barriers().get()->was_cleared(hal::LBRAMP)){
                 _logger->debug("LightBarrier Ramp was cleared");
    }
    if(_hal->get_light_barriers().get()->was_blocked(hal::LBEND)){
             _logger->debug("LightBarrier End was blocked");
    }
    if(_hal->get_light_barriers().get()->was_cleared(hal::LBEND)){
                 _logger->debug("LightBarrier End was cleared");
    }


}

void HalManager::handle_qnx_io_msg(dispatcher::cnnMngmnt::header_t header) {
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

HalManager::~HalManager() {
    _is_running = false;
    dispatcher::cnnMngmnt::QnxConnection(_irq_rec_channel->get_chid()).msg_send_pulse(1,
    _PULSE_CODE_UNBLOCK, 0);
    _listener_thread.join();
}

// Temporary
void HalManager::set_belt_state(bool value){
    if(value){
        _hal->get_cb_motor().get()->set_direction(FAST_FORWARDS);
    }
    else{
        _hal->get_cb_motor().get()->set_direction(STOP);
    }
}
// Temporary
void HalManager::set_junc_state(bool value){
    if(value){
        _hal->get_sorting_mechanism()->do_not_discard();
    }
    else{
        _hal->get_sorting_mechanism()->discard();
    }
}

} /* namespace hal */
