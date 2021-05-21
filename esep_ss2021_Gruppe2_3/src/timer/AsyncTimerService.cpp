/*
 * AsyncTimerService.cpp
 *
 *  Created on: 21.05.2021
 *      Author: jendr
 */

#include <timer/AsyncTimerService.h>

namespace timer {

AsyncTimerService::AsyncTimerService(const std::string& dispatcher_name) :
        DispatcherClient(dispatcher_name, "TIMER_SERVICE") {
    subscribe(dispatcher::EventType::EVNT_TIM_REQ);
}

void AsyncTimerService::handle(dispatcher::Event& event) {
    if (event.type == dispatcher::EventType::EVNT_TIM_REQ) {
        struct sigevent return_event;
        uint16_t alrt_val = get_alrt_from_event(event);
        SIGEV_PULSE_INIT(&return_event, _dispatcher_connection->get_id(), SIGEV_PULSE_PRIO_INHERIT,
                static_cast<int>(dispatcher::EventType::EVNT_TIM_ALRT), alrt_val);
        timer_t timerid;
        if (timer_create(CLOCK_REALTIME, &return_event, &timerid) != 0) {
            _logger->error("setting up os timer failed");
        }
        uint16_t milliseconds = get_ms_from_event(event);
        struct itimerspec timer;
        set_up_timer(&timer, milliseconds);
        timer_settime(timerid, 0, &timer, nullptr);
    }
}
void AsyncTimerService::set_up_timer(itimerspec * timer, int millisec) {
    // os timer needs seconds and nanoseconds
    int seconds = millisec / 1000;
    int nanoseconds = (millisec % 1000) * 1000 * 1000;
    timer->it_value.tv_sec = seconds;
    timer->it_value.tv_nsec = nanoseconds;
    // configure one shot timer
    timer->it_interval.tv_sec = 0;
    timer->it_interval.tv_nsec = 0;
}

uint16_t AsyncTimerService::get_ms_from_event(dispatcher::Event e) {
    return e.payload & 0xFFFF;
}

uint16_t AsyncTimerService::get_alrt_from_event(dispatcher::Event e) {
    return (e.payload & 0xFFFF0000) >> 16;
}

AsyncTimerService::~AsyncTimerService() {

}

} /* namespace hal */
