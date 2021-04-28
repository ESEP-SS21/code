/*
 * stoplight.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_ACTUATORS_STOPLIGHT_H_
#define SRC_ACTUATORS_STOPLIGHT_H_

#include "gpio.h"

enum Color {
		GREEN = 0,
		YELLOW,
		RED
};

enum Speed {
		SLOW,
		FAST
};

class Stoplight {
private:
	GPIO* gpio;

public:
	Stoplight(GPIO*);
	virtual ~Stoplight();

	void enable(Color);
	void disable(Color);
	void blink(Color, Speed);
};

#endif /* SRC_ACTUATORS_STOPLIGHT_H_ */
