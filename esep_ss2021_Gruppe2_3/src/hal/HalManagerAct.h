#pragma once

#include "dispatcher/connection_management/QnxChannel.h"
#include "dispatcher/connection_management/QnxConnection.h"
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

class HalManagerAct: public dispatcher::DispatcherClient {
public:
    HalManagerAct(const std::string& dispatcher_name);
    void handle(dispatcher::Event& event);
    void set_belt_state(bool value);
    void set_junc_state(bool value);
    virtual ~HalManagerAct();
private:
    Logger::Logger _logger { Logger::get() };
    std::shared_ptr<GPIOWrapper> _gpio;
    std::unique_ptr<HAL> _hal;
    void handle_qnx_io_msg(header_t header);
    std::unique_ptr<dispatcher::connection_management::QnxChannel> _irq_rec_channel;
    std::unique_ptr<dispatcher::connection_management::QnxConnection> _irq_connection; //connection used by isr
    bool _running;

};

} /* namespace hal */

