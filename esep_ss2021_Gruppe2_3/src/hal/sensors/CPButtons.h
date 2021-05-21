/*
 * CPButtons.h
 *
 *  Created on: 13.05.2021
 *      Author: morit
 */

#ifndef SRC_HAL_SENSORS_CPBUTTONS_H_
#define SRC_HAL_SENSORS_CPBUTTONS_H_

#include "../gpiowrapper.h"

namespace hal {

enum CPButtonType {
    CPSTART, CPSTOP, CPRESET
};
class CPButtons {

private:
    uint32_t _old_state_start;
    uint32_t _old_state_stop;
    uint32_t _old_state_reset;
    std::shared_ptr<GPIOWrapper> _gpio;
public:
    CPButtons(std::shared_ptr<GPIOWrapper> gpio);
    virtual ~CPButtons();
    bool was_pressed(CPButtonType);
    bool was_released(CPButtonType);
};

}

#endif /* SRC_HAL_SENSORS_CPBUTTONS_H_ */
