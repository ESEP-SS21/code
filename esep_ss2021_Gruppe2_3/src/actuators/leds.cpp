/*
 * leds.cpp
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#include "../actuators/leds.h"

namespace hal {

LEDs::LEDs(std::shared_ptr<GPIOWrapper> gpio) {
	_gpio = gpio;
}

LEDs::~LEDs() {
	delete &_gpio;
}

void LEDs::enable(LED_type led_type) {
	switch (led_type) {
	case START:
		_gpio->out(gpio_adresses::BANK_LED, gpio_adresses::LED_START_2, 1);
		break;
	case RESET:
		_gpio->out(gpio_adresses::BANK_LED, gpio_adresses::LED_RESET_2, 1);
		break;
	case Q1:
		_gpio->out(gpio_adresses::BANK_LED, gpio_adresses::LED_Q1_2, 1);
		break;
	default: // Q2
		_gpio->out(gpio_adresses::BANK_LED, gpio_adresses::LED_Q2_2, 1);
		break;
	}
}

void LEDs::disable(LED_type led_type) {
	switch (led_type) {
	case START:
		_gpio->out(gpio_adresses::BANK_LED, gpio_adresses::LED_START_2, 0);
		break;
	case RESET:
		_gpio->out(gpio_adresses::BANK_LED, gpio_adresses::LED_RESET_2, 0);
		break;
	case Q1:
		_gpio->out(gpio_adresses::BANK_LED, gpio_adresses::LED_Q1_2, 0);
		break;
	default: // Q2
		_gpio->out(gpio_adresses::BANK_LED, gpio_adresses::LED_Q2_2, 0);
		break;
	}
}

}
