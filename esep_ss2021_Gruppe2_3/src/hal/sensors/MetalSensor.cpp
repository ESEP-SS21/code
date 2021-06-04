/*
 * MetalSensor.cpp
 *
 *  Created on: 13.05.2021
 *      Author: morit
 */

#include <hal/sensors/MetalSensor.h>

namespace hal {

MetalSensor::MetalSensor(std::shared_ptr<GPIOWrapper> gpio) {
    _gpio = gpio;
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::METALLSENSOR_0);
    _not_metal_state = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::METALLSENSOR_0);

}

MetalSensor::~MetalSensor() {

}

bool MetalSensor::was_metal(){
    uint32_t in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::METALLSENSOR_0);
    bool ret = in > _not_metal_state;
    return ret;
}

}
