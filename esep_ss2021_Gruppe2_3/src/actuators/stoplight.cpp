/*
 * stoplight.cpp
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#include "../actuators/stoplight.h"

namespace hal {

Stoplight::Stoplight(std::shared_ptr<GPIOWrapper> gpio) {
	_gpio = gpio;
}

Stoplight::~Stoplight() {
	delete &_gpio;
}

void Stoplight::enable(Color color) {
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

	// TODO

	//switch (color) {
	//case GREEN:
	//	start_blinking(gpio_adresses::AMPEL_GRUEN_1, speed);
	//case YELLOW:
	//	start_blinking(gpio_adresses::AMPEL_GELB_1, speed);
	//default: // RED
	//	start_blinking(gpio_adresses::AMPEL_ROT_1, speed);
	//}
}

}

