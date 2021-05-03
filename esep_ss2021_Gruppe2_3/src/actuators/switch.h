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
	void do_not_discard() const override;
	void discard() const override;
	bool is_open() const override;
	void reset() const override;

};

}

#endif /* SRC_ACTUATORS_SWITCH_H_ */
