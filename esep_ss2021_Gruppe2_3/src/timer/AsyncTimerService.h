#ifndef SRC_TIMER_ASYNCTIMERSERVICE_H_
#define SRC_TIMER_ASYNCTIMERSERVICE_H_
#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/DispatcherClient.h"
namespace timer {

class AsyncTimerService: public dispatcher::DispatcherClient {
public:
    AsyncTimerService(const std::string& dispatcher_name);
    virtual ~AsyncTimerService();
    void handle(dispatcher::Event& event);
private:
    Logger::Logger _logger { Logger::get() };
    void set_up_timer(itimerspec * timer, int millisec);
    uint16_t get_ms_from_event(dispatcher::Event);
    uint16_t get_alrt_from_event(dispatcher::Event);
};

} /* namespace hal */

#endif /* SRC_TIMER_ASYNCTIMERSERVICE_H_ */
