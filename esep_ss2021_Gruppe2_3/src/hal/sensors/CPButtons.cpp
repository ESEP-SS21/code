/*
 * CPButtons.cpp
 *
 *  Created on: 13.05.2021
 *      Author: morit
 */

#include <hal/sensors/CPButtons.h>

namespace hal {

CPButtons::CPButtons(std::shared_ptr<GPIOWrapper> gpio){
    _gpio=gpio;

    _gpio->enable_interrupt_rising(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_START_0);
    _gpio->enable_interrupt_falling(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_START_0);
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_START_0);

    _gpio->enable_interrupt_rising(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_STOP_0);
    _gpio->enable_interrupt_falling(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_STOP_0);
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_STOP_0);

    _gpio->enable_interrupt_rising(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_RESET_0);
    _gpio->enable_interrupt_falling(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_RESET_0);
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::TASTE_RESET_0);

    _old_state_start = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_START_0);
    _old_state_stop = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_STOP_0);
    _old_state_reset = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_RESET_0);
}

bool CPButtons::was_pressed(CPButtonType cp_button_type){
    uint32_t in;
    bool ret;
    switch (cp_button_type){
    case CPSTART:
        in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_START_0);
        ret = in > _old_state_start;
        if(ret){
            _old_state_start = in;
        }
        return ret;
    case CPSTOP:
        in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_STOP_0);
        ret = in < _old_state_stop;
        if(ret){
            _old_state_stop = in;
        }
        return ret;
    default:
        in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_RESET_0);
        ret = in > _old_state_reset;
        if(ret){
            _old_state_reset = in;
        }
        return ret;
    }
}

bool CPButtons::was_released(CPButtonType cp_button_type){
    uint32_t in = 0;
    bool ret = false;
    switch (cp_button_type){
    case CPSTART:
        in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_START_0);
        ret = in < _old_state_start;
        if(ret){
            _old_state_start = in;
        }
        return ret;
    case CPSTOP:
        in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_STOP_0);
        ret = in > _old_state_stop;
        if(ret){
            _old_state_stop = in;
        }
        return ret;
    default:
        in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::TASTE_RESET_0);
        ret = in < _old_state_reset;
        if(ret){
            _old_state_reset = in;
        }
        return ret;
    }
}

CPButtons::~CPButtons(){

}
}



