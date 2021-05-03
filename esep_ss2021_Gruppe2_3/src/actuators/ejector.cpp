/*
 * ejector.cpp
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#include "../actuators/ejector.h"

namespace hal {

Ejector::Ejector(std::shared_ptr<GPIOWrapper> gpio) :
		SortingMechanism(gpio) {

}

void Ejector::open() const {
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::WEICHE_OEFFNEN_1,
			0);
}

void Ejector::close() const {
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::WEICHE_OEFFNEN_1,
			1);
}

bool Ejector::is_open() const {
	return _gpio->in(gpio_adresses::BANK_INPUT, gpio_adresses::WEICHE_OFFEN_0)
			== 0;
}

void Ejector::reset() const {
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::WEICHE_OEFFNEN_1,
			0);
}

}

