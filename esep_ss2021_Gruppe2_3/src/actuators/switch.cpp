/*
 * switch.cpp
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#include "../actuators/switch.h"

namespace hal {

Switch::Switch(std::shared_ptr<GPIOWrapper> gpio) : SortingMechanism(gpio) {

}

Switch::~Switch() {

}

void Switch::open() {

}

void Switch::close() {

}

bool Switch::is_open() {
	return 0;
}

}

