/*
 * sorting_mechanism.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_ACTUATORS_SORTING_MECHANISM_H_
#define SRC_ACTUATORS_SORTING_MECHANISM_H_

#include "../gpiowrapper.h"

namespace hal {

class SortingMechanism {
private:
	GPIOWrapper* gpio;

public:
	SortingMechanism(GPIOWrapper*);

	virtual void open()=0;
	virtual void close()=0;
	virtual bool is_open()=0;
};

}

#endif /* SRC_ACTUATORS_SORTING_MECHANISM_H_ */
