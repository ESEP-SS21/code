/*
 * LightBarriers.cpp
 *
 *  Created on: 13.05.2021
 *      Author: Lasse
 */

#include <hal/sensors/LightBarriers.h>

namespace hal {


LightBarriers::LightBarriers(std::shared_ptr<GPIOWrapper> gpio) {
    _gpio = gpio;
}

bool LightBarriers::was_blocked(LBType lb_type){
    return true;
}

bool LightBarriers::was_cleared(LBType lb_type){
    return true;
}

LightBarriers::~LightBarriers() {
    // TODO Auto-generated destructor stub
}

}
