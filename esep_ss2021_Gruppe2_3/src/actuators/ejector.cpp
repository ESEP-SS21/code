/*
 * ejector.cpp
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#include "../actuators/ejector.h"

namespace hal {

Ejector::Ejector(std::shared_ptr<GPIOWrapper> gpio) : SortingMechanism(gpio) {

}

Ejector::~Ejector() {

}

void Ejector::open() {

}

void Ejector::close() {

}

bool Ejector::is_open() {
	return 0;
}

}

