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
    _gpio->enable_interrupt_rising(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_EINLAUF_0);
    _gpio->enable_interrupt_falling(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_EINLAUF_0);
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_EINLAUF_0);

    _gpio->enable_interrupt_rising(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_HOEHENMESSUNG_0);
    _gpio->enable_interrupt_falling(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_HOEHENMESSUNG_0);
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_HOEHENMESSUNG_0);

    _gpio->enable_interrupt_rising(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_WEICHE_0);
    _gpio->enable_interrupt_falling(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_WEICHE_0);
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_WEICHE_0);

    _gpio->enable_interrupt_rising(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_RUTSCHE_0);
    _gpio->enable_interrupt_falling(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_RUTSCHE_0);
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_RUTSCHE_0);

    _gpio->enable_interrupt_rising(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_AUSLAUF_0);
    _gpio->enable_interrupt_falling(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_AUSLAUF_0);
    _gpio->enable_interrupt(gpio_adresses::BANK_INPUT,gpio_adresses::LICHTSCHRANKE_AUSLAUF_0);

    _old_state_start = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_EINLAUF_0);
    _old_state_heigth = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_HOEHENMESSUNG_0);
    _old_state_switch = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_WEICHE_0);
    _old_state_ramp = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_RUTSCHE_0);
    _old_state_end = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_AUSLAUF_0);
}

bool LightBarriers::was_blocked(LBType lb_type){
    uint32_t in;
    bool ret;

    switch (lb_type){
        case LBSTART:
            in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_EINLAUF_0);
            ret = in < _old_state_start;
            if(ret){
                _old_state_start = in;
            }
            return ret;
        case LBHEIGHT:
            in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_HOEHENMESSUNG_0);
            ret = in < _old_state_heigth;
            if(ret){
                _old_state_heigth = in;
            }
            return ret;
        case LBSWITCH:
            in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_WEICHE_0);
            ret = in < _old_state_switch;
            if(ret){
                _old_state_switch = in;
            }
            return ret;
        case LBRAMP:
            in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_RUTSCHE_0);
            ret = in < _old_state_ramp;
            if(ret){
                _old_state_ramp = in;
            }
            return ret;
        default:
            in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_AUSLAUF_0);
            ret = in < _old_state_end;
            if(ret){
                _old_state_end = in;
            }
            return ret;
    }
}

bool LightBarriers::was_cleared(LBType lb_type){
    uint32_t in;
    bool ret;
    switch (lb_type){
        case LBSTART:
            in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_EINLAUF_0);
            ret = in > _old_state_start;
            if(ret){
                _old_state_start = in;
            }
            return ret;
        case LBHEIGHT:
            in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_HOEHENMESSUNG_0);
            ret = in > _old_state_heigth;
            if(ret){
                _old_state_heigth = in;
            }
            return ret;
        case LBSWITCH:
            in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_WEICHE_0);
            ret = in > _old_state_switch;
            if(ret){
                _old_state_switch = in;
            }
            return ret;
        case LBRAMP:
            in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_RUTSCHE_0);
            ret = in > _old_state_ramp;
            if(ret){
                _old_state_ramp = in;
            }
            return ret;
        default:
            in = _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::LICHTSCHRANKE_AUSLAUF_0);
            ret = in > _old_state_end;
            if(ret){
                _old_state_end = in;
            }
            return ret;
    }
}

LightBarriers::~LightBarriers() {
    // TODO Auto-generated destructor stub
}

}
