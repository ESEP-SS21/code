/*
 * ejector.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_ACTUATORS_EJECTOR_H_
#define SRC_ACTUATORS_EJECTOR_H_

#include "../actuators/sorting_mechanism.h"

class Ejector: public SortingMechanism {
public:
	virtual ~Ejector();

	virtual void open();
	virtual void close();
	virtual bool is_open();

};

#endif /* SRC_ACTUATORS_EJECTOR_H_ */
