/*
 * EStop.cpp
 *
 *  Created on: 12.05.2021
 *      Author: jendr
 */

#include <hal/sensors/EStop.h>

namespace hal {

EStop::EStop(std::shared_ptr<GPIOWrapper> gpio) {
    _gpio=gpio;
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_ESTOPP_0);
    _gpio->enable_interrupt_rising(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_ESTOPP_0);
    _gpio->enable_interrupt_falling(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_ESTOPP_0);
}

bool EStop::is_pressed(){
    return true;
}

EStop::~EStop() {
    // TODO Auto-generated destructor stub
}

} /* namespace hal */
