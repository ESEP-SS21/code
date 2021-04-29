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
	//static HAL* _instance;

	HAL();

	std::shared_ptr<LEDs> _leds;
	std::shared_ptr<SortingMechanism> _sorting_mechanism;
	std::shared_ptr<CBMotor> _cb_motor;
	std::shared_ptr<Stoplight> _stoplight;

public:
	static HAL& get_instance() {
		static HAL _instance;
		return _instance;
	}

	~HAL();

	std::shared_ptr<LEDs> get_leds() const;
	std::shared_ptr<SortingMechanism> get_sorting_mechanism() const;
	std::shared_ptr<CBMotor> get_cb_motor() const;
	std::shared_ptr<Stoplight> get_stoplight() const;
};

}

#endif /* SRC_HAL_H_ */
