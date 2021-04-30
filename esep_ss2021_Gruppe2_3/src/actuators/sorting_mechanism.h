/*
 * sorting_mechanism.h
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#ifndef SRC_ACTUATORS_SORTING_MECHANISM_H_
#define SRC_ACTUATORS_SORTING_MECHANISM_H_

#include "../gpiowrapper.h"

namespace hal {

class SortingMechanism {
protected:
	std::shared_ptr<GPIOWrapper> _gpio;

public:
	SortingMechanism(std::shared_ptr<GPIOWrapper> gpio);
	~SortingMechanism();

	virtual void open() const = 0;
	virtual void close() const = 0;
	virtual bool is_open() const = 0;
};

}

#endif /* SRC_ACTUATORS_SORTING_MECHANISM_H_ */
