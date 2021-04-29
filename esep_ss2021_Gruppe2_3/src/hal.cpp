/*
 * hal.cpp
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#include "hal.h"
#include <memory>

namespace hal {

HAL& HAL::get_instance() {
	static HAL _instance;
	return _instance;
}

HAL::HAL() {
	auto gpio_shptr = std::make_shared<GPIOWrapper>();

	_leds = std::unique_ptr<LEDs>(new LEDs(gpio_shptr));
	_cb_motor = std::unique_ptr<CBMotor>(new CBMotor(gpio_shptr));
	_stoplight = std::unique_ptr<Stoplight>(new Stoplight(gpio_shptr));
	_sorting_mechanism = std::unique_ptr<SortingMechanism>(
			new Switch(gpio_shptr));
}

HAL::~HAL() {
	delete &_leds;
	delete &_cb_motor;
	delete &_stoplight;
	delete &_sorting_mechanism;
}

std::unique_ptr<LEDs> HAL::get_leds() {
	return move(_leds);
}

std::unique_ptr<SortingMechanism> HAL::get_sorting_mechanism() {
	return move(_sorting_mechanism);
}

std::unique_ptr<CBMotor> HAL::get_cb_motor() {
	return move(_cb_motor);
}

std::unique_ptr<Stoplight> HAL::get_stoplight() {
	return move(_stoplight);
}

}

