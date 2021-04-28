/*
 * gpio.h
 *
 *  Created on: 28.04.2021
 *      Author: justi
 */

#ifndef SRC_ACTUATORS_GPIO_H_
#define SRC_ACTUATORS_GPIO_H_

#include <cstdint>

namespace hal {

class GPIOWrapper {
private:
	uintptr_t _bank_input;
	uintptr_t _bank_actuator;
	uintptr_t _bank_led;

	void add_bit_to_register(uint32_t, const uint32_t, uint32_t);
	void set_bit_in_register(uint32_t, const uint32_t, uint32_t);
	void write_value_to_register(uint32_t, const uint32_t, uint32_t);
	uint32_t read_value_from_register(uint32_t, const uint32_t, uint32_t);

public:
	GPIOWrapper();
	virtual ~GPIOWrapper();

	void out(uint32_t bank, uint32_t pin, uint32_t value);
	uint32_t in(uint32_t bank, uint32_t pin);
	void enable_interrupt(uint32_t bank, uint32_t pin);
	void disable_interrupt(uint32_t bank, uint32_t pin);
	void enable_debounce(uint32_t bank, uint32_t pin);
	void set_debounce_time(uint32_t bank, uint32_t time_ms);
	void enable_interrupt_falling(uint32_t bank, uint32_t pin);
	void enable_interrupt_rising(uint32_t bank, uint32_t pin);
};

}

#endif /* SRC_ACTUATORS_GPIO_H_ */
