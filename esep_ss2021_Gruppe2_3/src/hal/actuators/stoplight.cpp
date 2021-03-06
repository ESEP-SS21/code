#include "../actuators/stoplight.h"

namespace hal {
using namespace dispatcher;

Stoplight::Stoplight(std::shared_ptr<GPIOWrapper> gpio) :
        _blinker(gpio) {
    _gpio = gpio;
    _blinker_thread = std::thread(&BlinkWorker::run, &_blinker);
}

Stoplight::~Stoplight() {
    _blinker.stop_loop();
    _blinker_thread.join();
    disable(Color::RED);
    disable(Color::YELLOW);
    disable(Color::GREEN);
}

void Stoplight::enable(Color color) {
    _blinker.stop_blinking();
    switch (color) {
    case GREEN:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, 1);
        break;
    case YELLOW:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, 1);
        break;
    case RED:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 1);
         break;
    case ALL:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, 1);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, 1);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 1);
        break;
    default:
        _logger->error("Unknown Color");
    }
}

void Stoplight::disable(Color color) {
    _blinker.stop_blinking();
    switch (color) {
    case GREEN:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, 0);
        break;
    case YELLOW:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, 0);
        break;
    case RED:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 0);
        break;
    case ALL:
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, 0);
        _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 0);
        break;
    default:
        _logger->error("Unknown Color");
    }
}

void Stoplight::blink(Color color, Speed speed) {
    if (speed == hal::FAST) {
        _blinker.set_duty_cycle(500);
    } else {
        _blinker.set_duty_cycle(1000);
    }
    _blinker.start_blinking(color);
}

}

