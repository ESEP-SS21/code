/*
 * sorting_mechanism.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_ACTUATORS_SORTING_MECHANISM_H_
#define SRC_ACTUATORS_SORTING_MECHANISM_H_

#include "gpio.h"

class SortingMechanism {
private:
	GPIO* gpio;

public:
	SortingMechanism(GPIO*);

	virtual void open()=0;
	virtual void close()=0;
	virtual bool is_open()=0;
};

#endif /* SRC_ACTUATORS_SORTING_MECHANISM_H_ */
