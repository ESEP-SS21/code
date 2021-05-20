#ifndef SRC_ACTUATORS_BLINKWORKER_H_
#define SRC_ACTUATORS_BLINKWORKER_H_

#include <mutex>
#include <thread>
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
    bool _running;
    useconds_t _duty_cycle;
    hal::Color _color;
    std::mutex _blink_lock;

};

} /* namespace hal */

#endif /* SRC_ACTUATORS_BLINKWORKER_H_ */
