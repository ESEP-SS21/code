#ifndef SRC_ACTUATORS_STOPLIGHT_H_
#define SRC_ACTUATORS_STOPLIGHT_H_

#include "../gpiowrapper.h"
#include "../actuators/BlinkWorker.h"
#include "color.h"

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
    void enable(Color);
    void disable(Color);
    void blink(Color, Speed);
};

}

#endif /* SRC_ACTUATORS_STOPLIGHT_H_ */
