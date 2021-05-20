#ifndef SRC_ACTUATORS_LEDS_H_
#define SRC_ACTUATORS_LEDS_H_

#include "../gpiowrapper.h"

namespace hal {

enum LED_type {
	START = 0, RESET, Q1, Q2
};

class LEDs {
private:
	std::shared_ptr<GPIOWrapper> _gpio;

public:
	LEDs(std::shared_ptr<GPIOWrapper>);
	virtual ~LEDs() = default;
	void enable(LED_type);
	void disable(LED_type);
};

}

#endif /* SRC_ACTUATORS_LEDS_H_ */
