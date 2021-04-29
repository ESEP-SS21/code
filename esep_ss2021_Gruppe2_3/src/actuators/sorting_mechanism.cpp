/*
 * sorting_mechanism.cpp
 *
 *  Created on: 29.04.2021
 *      Author: justi
 */
#include "sorting_mechanism.h"

namespace hal {

SortingMechanism::SortingMechanism(std::shared_ptr<GPIOWrapper> gpio) {
	_gpio = gpio;
}

SortingMechanism::~SortingMechanism() {
	delete &_gpio;
}

}

