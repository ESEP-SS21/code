/*
 * stoplight.cpp
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#include "../actuators/stoplight.h"


namespace hal {

Stoplight::Stoplight(std::shared_ptr<GPIOWrapper> gpio): _blinker(gpio) {
	_gpio = gpio;
	_blinker_thread = std::thread(&BlinkWorker::run, &_blinker);
}

Stoplight::~Stoplight(){
	_blinker.stop_loop();
	_blinker_thread.join();
}

void Stoplight::enable(Color color) {
	_blinker.stop_blinking();
	switch (color) {
	case GREEN:
		_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1,
				1);
		break;
	case YELLOW:
		_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1,
				1);
		break;
	default: // RED
		_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 1);
		break;
	}
}

void Stoplight::disable(Color color) {
	_blinker.stop_blinking();
	switch (color) {
	case GREEN:
		_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1,
				0);
		break;
	case YELLOW:
		_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1,
				0);
		break;
	default: // RED
		_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 0);
		break;
	}
}

void Stoplight::blink(Color color, Speed speed) {
	if(speed == hal::FAST){
		_blinker.set_duty_cycle(500);
	}
	else{
		_blinker.set_duty_cycle(1000);
	}
	_blinker.start_blinking(color);
}

}

