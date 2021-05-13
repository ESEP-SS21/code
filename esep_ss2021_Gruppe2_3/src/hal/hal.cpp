#include "hal.h"
#include <memory>
#include "simqnxirqapi.h"
#include "simqnxgpioapi.h" // must be last include !!!

namespace hal {

HAL::HAL(std::shared_ptr<GPIOWrapper> gpio_shptr) {

    _leds = std::shared_ptr<LEDs>(new LEDs(gpio_shptr));
    _cb_motor = std::shared_ptr<CBMotor>(new CBMotor(gpio_shptr));
    _stoplight = std::shared_ptr<Stoplight>(new Stoplight(gpio_shptr));
    _sorting_mechanism = std::shared_ptr<SortingMechanism>(new Switch(gpio_shptr));
    _estop = std::shared_ptr<EStop>(new EStop(gpio_shptr));
}

std::shared_ptr<LEDs> HAL::get_leds() const {
    return _leds;
}

std::shared_ptr<SortingMechanism> HAL::get_sorting_mechanism() const {
    return _sorting_mechanism;
}

std::shared_ptr<CBMotor> HAL::get_cb_motor() const {
    return _cb_motor;
}

std::shared_ptr<Stoplight> HAL::get_stoplight() const {
    return _stoplight;
}

}

