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
	// TODO Auto-generated destructor stub
}

void LEDs::enable(LED_type) {

}

void LEDs::disable(LED_type) {

}

}
