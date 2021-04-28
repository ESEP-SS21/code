/*
 * leds.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_ACTUATORS_LEDS_H_
#define SRC_ACTUATORS_LEDS_H_

#include "../gpiowrapper.h"

namespace hal {

enum LED_type {
	START = 0, RESET, Q1, Q2
};

class LEDs {
private:
	GPIOWrapper* gpio;

public:
	LEDs(GPIOWrapper*);
	virtual ~LEDs();

	void enable(LED_type);
	void disable(LED_type);
};

}

#endif /* SRC_ACTUATORS_LEDS_H_ */
