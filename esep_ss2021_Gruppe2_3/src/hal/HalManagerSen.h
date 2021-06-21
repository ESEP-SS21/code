#pragma once

#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"
#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include "gpiowrapper.h"
#include "hal.h"
#include <chrono>
#include <sys/dispatch.h>

namespace hal {

static constexpr uint32_t GPIO_IRQ_NR = 97;
static constexpr uint32_t ADC_IRQ_NR = 16;
static constexpr uint32_t PULSE_GPIO_IRQ = 17;
static constexpr uint32_t PULSE_ADC_IRQ = 18;

class HalManagerSen: public dispatcher::DispatcherClient {
public:
    HalManagerSen(const std::string& dispatcher_name, bool playback_mode);
    void handle(dispatcher::Event& event) override;
    virtual ~HalManagerSen();
private:
    bool _pb_mode;
    Logger::Logger _logger { Logger::get() };
    std::shared_ptr<GPIOWrapper> _gpio;
    std::unique_ptr<HAL> _hal;
    void handle_qnx_io_msg(header_t header);
    std::unique_ptr<dispatcher::cnnMngmnt::QnxChannel> _irq_rec_channel;
    std::unique_ptr<dispatcher::cnnMngmnt::QnxConnection> _irq_connection; //connection used by isr
    std::thread _listener_thread;
    bool _running;
    void int_rec_fnct();
    void send_event_to_dispatcher();
    std::chrono::time_point<std::chrono::high_resolution_clock> _start_pressed_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> _stop_pressed_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> _reset_pressed_time;
};

} /* namespace hal */

