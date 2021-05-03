/*
 * switch.cpp
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#include "../actuators/switch.h"

namespace hal {

Switch::Switch(std::shared_ptr<GPIOWrapper> gpio) :
		SortingMechanism(gpio) {

}

void Switch::open() const {
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::WEICHE_OEFFNEN_1,
			1);
}

void Switch::close() const {
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::WEICHE_OEFFNEN_1,
			0);
}

bool Switch::is_open() const {
	return _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::WEICHE_OFFEN_0)
			== 1;
}

void Switch::reset() const {
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::WEICHE_OEFFNEN_1,
			0);
}

}

