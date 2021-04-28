/*
 * hal.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_HAL_H_
#define SRC_HAL_H_

#include "actuators/leds.h"
#include "actuators/sorting_mechanism.h"
#include "actuators/cb_motor.h"
#include "actuators/stoplight.h"
#include "gpiowrapper.h"

class HAL {
private:
	HAL* _instance;
	HAL();

	GPIOWrapper* gpio;
	LEDs* leds;
	SortingMechanism* sorting_mechanism;
	CBMotor* cb_motor;
	Stoplight* stoplight;

public:
	virtual ~HAL();

	HAL* get_instance();
	LEDs* get_leds();
	SortingMechanism* get_eject_mechanism();
	CBMotor* get_cb_motor();
	Stoplight* get_stoplight();

};

#endif /* SRC_HAL_H_ */
