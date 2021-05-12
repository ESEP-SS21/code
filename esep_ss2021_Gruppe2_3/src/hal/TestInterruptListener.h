/*
 * TestInterruptListener.h
 *
 *  Created on: 12.05.2021
 *      Author: jendr
 */

#ifndef SRC_HAL_TESTINTERRUPTLISTENER_H_
#define SRC_HAL_TESTINTERRUPTLISTENER_H_
#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include <stdint.h>
#include <sys/neutrino.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include "gpiowrapper.h"
#include "simulation/simulationadapterqnx/simqnxirqapi.h"
#include "simulation/simulationadapterqnx/simqnxgpioapi.h"

namespace hal {

static constexpr uint32_t GPIO_IRQ_NR = 97;
static constexpr uint32_t PULSE_GPIO_IRQ = 17;


class TestInterruptListener {
public:
    TestInterruptListener(std::shared_ptr<GPIOWrapper>);
    virtual ~TestInterruptListener();
private:
    Logger::Logger _logger { Logger::get() };
    std::shared_ptr<GPIOWrapper> _gpio;
    std::unique_ptr<dispatcher::cnnMngmnt::QnxChannel> _irq_rec_channel;
    std::unique_ptr<dispatcher::cnnMngmnt::QnxConnection> _irq_connection; //connection used by isr
    std::thread _listener_thread;
    bool _is_running;
    void run();
    void handle_qnx_io_msg(dispatcher::cnnMngmnt::header_t header);
    struct sigevent _input_event;
};

} /* namespace hal */

#endif /* SRC_HAL_TESTINTERRUPTLISTENER_H_ */
