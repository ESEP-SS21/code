/*
 * MetalSensor.cpp
 *
 *  Created on: 13.05.2021
 *      Author: morit
 */

#include <hal/sensors/MetalSensor.h>

namespace hal {

MetalSensor::MetalSensor(std::shared_ptr<GPIOWrapper> gpio) {
    // TODO Auto-generated constructor stub

}

MetalSensor::~MetalSensor() {
    // TODO Auto-generated destructor stub
}

bool MetalSensor::was_metal(){
    return true;
}

}
