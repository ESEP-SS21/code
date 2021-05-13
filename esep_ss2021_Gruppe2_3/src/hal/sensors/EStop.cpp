/*
 * EStop.cpp
 *
 *  Created on: 12.05.2021
 *      Author: jendr
 */

#include <hal/sensors/EStop.h>

namespace hal {

EStop::EStop(std::shared_ptr<GPIOWrapper> gpio){
    _gpio=gpio;
    _gpio->enable_interrupt_rising(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_ESTOPP_0);
    _gpio->enable_interrupt_falling(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_ESTOPP_0);
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_ESTOPP_0);
    _bit_state = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_ESTOPP_0);
}

bool EStop::was_pressed(){
    uint32_t in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_ESTOPP_0);
    return in < _bit_state;

}

bool EStop::was_released(){
   uint32_t in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_ESTOPP_0);
   bool ret = in >_bit_state;
   _bit_state = in;
   return ret;
}

EStop::~EStop() {
    // TODO Auto-generated destructor stub
}

} /* namespace hal */
