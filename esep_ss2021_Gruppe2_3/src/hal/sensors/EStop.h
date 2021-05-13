#ifndef SRC_HAL_SENSORS_ESTOP_H_
#define SRC_HAL_SENSORS_ESTOP_H_

#include "../gpiowrapper.h"

namespace hal {

class EStop {
public:
    EStop(std::shared_ptr<GPIOWrapper> gpio);
    bool was_pressed();
    bool was_released();
    virtual ~EStop();
private:
    uint32_t _bit_state;
    std::shared_ptr<GPIOWrapper> _gpio;
};

} /* namespace hal */

#endif /* SRC_HAL_SENSORS_ESTOP_H_ */
