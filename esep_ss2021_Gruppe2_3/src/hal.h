/*
 * hal.h
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#ifndef SRC_HAL_H_
#define SRC_HAL_H_

#include "actuators/leds.h"
#include "actuators/sorting_mechanism.h"
#include "actuators/switch.h"
#include "actuators/ejector.h"
#include "actuators/cb_motor.h"
#include "actuators/stoplight.h"
#include "gpiowrapper.h"

namespace hal {

class HAL {
private:
	static HAL _instance;

	std::unique_ptr<LEDs> _leds;
	std::unique_ptr<SortingMechanism> _sorting_mechanism;
	std::unique_ptr<CBMotor> _cb_motor;
	std::unique_ptr<Stoplight> _stoplight;

	HAL();
	~HAL();

public:
	static HAL& get_instance() {
		return _instance;
	}

	std::unique_ptr<LEDs> get_leds();
	std::unique_ptr<SortingMechanism> get_eject_mechanism();
	std::unique_ptr<CBMotor> get_cb_motor();
	std::unique_ptr<Stoplight> get_stoplight();
};

}

#endif /* SRC_HAL_H_ */
