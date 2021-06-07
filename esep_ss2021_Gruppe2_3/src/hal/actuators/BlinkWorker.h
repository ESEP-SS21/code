#ifndef SRC_ACTUATORS_BLINKWORKER_H_
#define SRC_ACTUATORS_BLINKWORKER_H_

#include <mutex>
#include <thread>
#include <atomic>
#include "../gpiowrapper.h"
#include "color.h"
#include <chrono>

namespace hal {

class BlinkWorker {
public:
    BlinkWorker(std::shared_ptr<GPIOWrapper>);
    BlinkWorker(const BlinkWorker&);
    void run();
    void set_duty_cycle(const uint32_t milliseconds = 1000);
    void start_blinking(Color);
    void stop_blinking();
    void stop_loop();
    virtual ~BlinkWorker();

private:
    std::shared_ptr<GPIOWrapper> _gpio;
    std::atomic<bool> _running;
    std::atomic<bool> _interrupted;
    useconds_t _duty_cycle;
    hal::Color _color;
    std::mutex _mutex;
    std::condition_variable _cv;
};

} /* namespace hal */

#endif /* SRC_ACTUATORS_BLINKWORKER_H_ */
