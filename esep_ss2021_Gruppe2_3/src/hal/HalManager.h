/*
 * TestInterruptListener.h
 *
 *  Created on: 12.05.2021
 *      Author: jendr
 */

#ifndef SRC_HAL_HALMANAGER_H_
#define SRC_HAL_HALMANAGER_H_
#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include "gpiowrapper.h"
#include "hal.h"

namespace hal {

static constexpr uint32_t GPIO_IRQ_NR = 97;
static constexpr uint32_t PULSE_GPIO_IRQ = 17;


class HalManager {
public:
    HalManager();
    void set_belt_state(bool value);
    void set_junc_state(bool value);
    virtual ~HalManager();
private:
    Logger::Logger _logger { Logger::get() };
    std::shared_ptr<GPIOWrapper> _gpio;
    std::unique_ptr<HAL>_hal;
    void handle_qnx_io_msg(dispatcher::cnnMngmnt::header_t header);
    std::unique_ptr<dispatcher::cnnMngmnt::QnxChannel> _irq_rec_channel;
    std::unique_ptr<dispatcher::cnnMngmnt::QnxConnection> _irq_connection; //connection used by isr
    std::thread _listener_thread;

    bool _is_running;
    void int_rec_fnct();
    void send_event_to_dispatcher();
};

} /* namespace hal */

#endif /* SRC_HAL_HALMANAGER_H_ */
