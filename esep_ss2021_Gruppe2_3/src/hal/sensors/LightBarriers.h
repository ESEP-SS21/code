/*
 * LightBarriers.h
 *
 *  Created on: 13.05.2021
 *      Author: Lasse
 */

#ifndef SRC_HAL_SENSORS_LIGHTBARRIERS_H_
#define SRC_HAL_SENSORS_LIGHTBARRIERS_H_

#include "../gpiowrapper.h"

namespace hal {

enum LBType {
    LBSTART, LBHEIGHT, LBSWITCH, LBRAMP, LBEND
};

class LightBarriers {
private:
    int _old_state_start;
    int _old_state_heigth;
    int _old_state_switch;
    int _old_state_ramp;
    int _old_state_end;
    std::shared_ptr<GPIOWrapper> _gpio;
public:
    LightBarriers(std::shared_ptr<GPIOWrapper> gpio);
    virtual ~LightBarriers();
    bool was_blocked(LBType);
    bool was_cleared(LBType);

};

}

#endif /* SRC_HAL_SENSORS_LIGHTBARRIERS_H_ */
