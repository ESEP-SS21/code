/*
 * gpio.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_ACTUATORS_GPIO_H_
#define SRC_ACTUATORS_GPIO_H_

#include <cstdint>

class GPIO {
private:
	uintptr_t _bank_input;
	uintptr_t _bank_actuator;
	uintptr_t _bank_led;

public:
	GPIO();
	virtual ~GPIO();

	void write(int bank, int pin);
	void read(int bank, int pin);
	void enable_interrupt(int bank, int pin);
	void disable_interrupt(int bank, int pin);
	void enable_debounce(int bank, int pin);
	void set_debounce_time(int bank, int pin);
	void enable_interrupt_falling(int bank, int pin);
	void enable_interrupt_rising(int bank, int pin);
};

#endif /* SRC_ACTUATORS_GPIO_H_ */
