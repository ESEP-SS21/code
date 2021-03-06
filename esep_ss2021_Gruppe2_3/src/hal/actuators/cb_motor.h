#ifndef SRC_ACTUATORS_CB_MOTOR_H_
#define SRC_ACTUATORS_CB_MOTOR_H_

#include "../gpiowrapper.h"
#include <memory>

namespace hal {

enum Direction {
    FAST_FORWARDS = 0, SLOW_FORWARDS, STOP, SLOW_BACKWARDS, FAST_BACKWARDS
};

class CBMotor {
private:
    std::shared_ptr<GPIOWrapper> _gpio;

public:
    CBMotor(std::shared_ptr<GPIOWrapper>);
    virtual ~CBMotor() = default;
    void set_direction(Direction);
};

}

#endif /* SRC_ACTUATORS_CB_MOTOR_H_ */
