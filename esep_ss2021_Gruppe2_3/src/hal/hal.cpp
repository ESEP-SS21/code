#include "hal.h"
#include <memory>
#include "simqnxirqapi.h"
#include "simqnxgpioapi.h" // must be last include !!!

namespace hal {

HAL::HAL(std::shared_ptr<GPIOWrapper> gpio_shptr) {

    _leds = std::shared_ptr<LEDs>(new LEDs(gpio_shptr));
    _cb_motor = std::shared_ptr<CBMotor>(new CBMotor(gpio_shptr));
    _stoplight = std::shared_ptr<Stoplight>(new Stoplight(gpio_shptr));
    //check if the ejector sensor is on by default and select the sort mechanism
    int is_pusher = gpio_shptr->in(gpio_adresses::BANK_INPUT, gpio_adresses::WEICHE_OFFEN_0);
    if(is_pusher){
        _sorting_mechanism = std::shared_ptr<SortingMechanism>(new Ejector(gpio_shptr));
    }
    else{
        _sorting_mechanism = std::shared_ptr<SortingMechanism>(new Switch(gpio_shptr));
    }
    _estop = std::shared_ptr<EStop>(new EStop(gpio_shptr));
    _light_barriers = std::shared_ptr<LightBarriers>(new LightBarriers(gpio_shptr));
    _height_sensor = std::shared_ptr<HeightSensor>(new HeightSensor());
    _cp_buttons = std::shared_ptr<CPButtons>(new CPButtons(gpio_shptr));
    _metal_sensor = std::shared_ptr<MetalSensor>(new MetalSensor(gpio_shptr));
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

std::shared_ptr<EStop> HAL::get_estop() const {
    return _estop;
}

std::shared_ptr<LightBarriers> HAL::get_light_barriers() const {
    return _light_barriers;
}

std::shared_ptr<HeightSensor> HAL::get_height_sensor() const {
    return _height_sensor;
}

std::shared_ptr<CPButtons> HAL::get_cp_buttons() const {
    return _cp_buttons;
}

std::shared_ptr<MetalSensor> HAL::get_metal_sensor() const {
    return _metal_sensor;
}

}

