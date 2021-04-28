/*
 * cb_motor.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_ACTUATORS_CB_MOTOR_H_
#define SRC_ACTUATORS_CB_MOTOR_H_

#include "gpio.h"

enum Direction {
		FAST_FORWARDS = 0,
		SLOW_FORWARDS,
		STOP,
		SLOW_BACKWARDS,
		FAST_BACKWARDS
};

class CBMotor {
private:
	GPIO* gpio;

public:
	CBMotor(GPIO*);
	virtual ~CBMotor();

	void set_direction(Direction);
};

#endif /* SRC_ACTUATORS_CB_MOTOR_H_ */
