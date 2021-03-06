#include "../actuators/cb_motor.h"

namespace hal {

CBMotor::CBMotor(std::shared_ptr<GPIOWrapper> gpio) {
    _gpio = gpio;
}

void CBMotor::set_direction(Direction direction) {
    switch (direction) {
    case FAST_FORWARDS:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_STOP_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_LANGSAM_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_LINKS_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_RECHTS_1, 1);
        break;
    case SLOW_FORWARDS:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_STOP_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_LINKS_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_LANGSAM_1, 1);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_RECHTS_1, 1);
        break;
    case FAST_BACKWARDS:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_STOP_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_LANGSAM_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_RECHTS_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_LINKS_1, 1);
        break;
    case SLOW_BACKWARDS:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_STOP_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_RECHTS_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_LANGSAM_1, 1);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_LINKS_1, 1);
        break;
    default:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_LANGSAM_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_LINKS_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_RECHTS_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::MOTOR_STOP_1, 1);
    }
}

}

