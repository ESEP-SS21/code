/*
 * ejector.h
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#ifndef SRC_ACTUATORS_EJECTOR_H_
#define SRC_ACTUATORS_EJECTOR_H_

#include "../actuators/sorting_mechanism.h"

namespace hal {

class Ejector: public SortingMechanism {
public:
	Ejector(std::shared_ptr<GPIOWrapper>);

	void open() override;
	void close() override;
	bool is_open() override;

};

}

#endif /* SRC_ACTUATORS_EJECTOR_H_ */
