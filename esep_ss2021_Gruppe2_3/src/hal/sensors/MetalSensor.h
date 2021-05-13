/*
 * MetalSensor.h
 *
 *  Created on: 13.05.2021
 *      Author: morit
 */

#ifndef SRC_HAL_SENSORS_METALSENSOR_H_
#define SRC_HAL_SENSORS_METALSENSOR_H_

#include "../gpiowrapper.h"

namespace hal {

class MetalSensor {

public:
    MetalSensor(std::shared_ptr<GPIOWrapper> gpio);
    virtual ~MetalSensor();
    bool was_metal();
private:
    uint32_t _old_state;
    std::shared_ptr<GPIOWrapper> _gpio;
};
}

#endif /* SRC_HAL_SENSORS_METALSENSOR_H_ */
