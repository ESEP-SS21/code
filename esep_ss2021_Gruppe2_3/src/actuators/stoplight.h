/*
 * stoplight.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_ACTUATORS_STOPLIGHT_H_
#define SRC_ACTUATORS_STOPLIGHT_H_

#include "../gpiowrapper.h"

namespace hal{

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
	GPIOWrapper* gpio;

public:
	Stoplight(GPIOWrapper*);
	virtual ~Stoplight();

	void enable(Color);
	void disable(Color);
	void blink(Color, Speed);
};
}

#endif /* SRC_ACTUATORS_STOPLIGHT_H_ */
