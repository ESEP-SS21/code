#ifndef SRC_ACTUATORS_STOPLIGHT_H_
#define SRC_ACTUATORS_STOPLIGHT_H_

#include "../../dispatcher/color.h"
#include "../gpiowrapper.h"
#include "../actuators/BlinkWorker.h"

namespace hal {

enum Speed {
    SLOW, FAST
};

class Stoplight {
private:
    std::shared_ptr<GPIOWrapper> _gpio;
    BlinkWorker _blinker;
    std::thread _blinker_thread;

public:
    Stoplight(std::shared_ptr<GPIOWrapper>);
    virtual ~Stoplight();
    void enable(dispatcher::Color);
    void disable(dispatcher::Color);
    void blink(dispatcher::Color, Speed);
};

}

#endif /* SRC_ACTUATORS_STOPLIGHT_H_ */
