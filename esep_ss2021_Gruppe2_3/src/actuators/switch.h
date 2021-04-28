/*
 * switch.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_ACTUATORS_SWITCH_H_
#define SRC_ACTUATORS_SWITCH_H_

#include "../actuators/sorting_mechanism.h"

namespace hal {

class Switch: public SortingMechanism {
public:
	virtual ~Switch();

	virtual void open();
	virtual void close();
	virtual bool is_open();

};

}

#endif /* SRC_ACTUATORS_SWITCH_H_ */
