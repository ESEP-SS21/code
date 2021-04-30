/*
 * switch.h
 *
 *  Created on: 28.04.2021
 *      Author: Justin Hoffmann
 */

#ifndef SRC_ACTUATORS_SWITCH_H_
#define SRC_ACTUATORS_SWITCH_H_

#include "../actuators/sorting_mechanism.h"

namespace hal {

class Switch: public SortingMechanism {
public:
	Switch(std::shared_ptr<GPIOWrapper>);

	void open() const override;
	void close() const override;
	bool is_open() const override;

};

}

#endif /* SRC_ACTUATORS_SWITCH_H_ */
