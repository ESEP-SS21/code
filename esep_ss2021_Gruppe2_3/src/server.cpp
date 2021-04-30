/* Simple demostration of the simulator usage
 * @author: Franz Korf
 * @author: Thomas Lehmann
 * @date: 2020-04-24
 */
#include <iostream>
#include "simqnxgpioapi.h" // must be last include !!!
#include "gpiowrapper.h"
#include "hal.h"
#include "cb_motor.h"

#ifdef TEST_ENABLE

#include <gtest/gtest.h>
#include "tests.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	auto result = RUN_ALL_TESTS();

#else

//TODO blinken der Stoplight in Thread
//TODO XOR der SortingMechanisms in der HAL

int main(int argc, char **argv) {
	hal::HAL::get_instance().get_stoplight().get()->blink(hal::GREEN, hal::SLOW);
	usleep(5000 *1000);
	hal::HAL::get_instance().get_stoplight().get()->disable(hal::GREEN);
	usleep(2000 *1000);
	hal::HAL::get_instance().get_stoplight().get()->blink(hal::GREEN, hal::SLOW);

	/*
	while (1) {
		//CBMotor
		hal::HAL::get_instance().get_cb_motor().get()->set_direction(hal::FAST_FORWARDS);
		usleep(1000 * 500);

		hal::HAL::get_instance().get_cb_motor().get()->set_direction(hal::FAST_BACKWARDS);
		usleep(1000 * 500);

		hal::HAL::get_instance().get_cb_motor().get()->set_direction(hal::SLOW_BACKWARDS);
		usleep(1000 * 500);

		hal::HAL::get_instance().get_cb_motor().get()->set_direction(hal::SLOW_FORWARDS);
		usleep(1000 * 500);

		hal::HAL::get_instance().get_cb_motor().get()->set_direction(hal::STOP);
		usleep(1000 * 500);

		//SortingMechanism
		hal::HAL::get_instance().get_sorting_mechanism().get()->open();
		usleep(1000 * 500);

		std::cout << hal::HAL::get_instance().get_sorting_mechanism().get()->is_open() << std::endl;
		usleep(1000 * 500);

		hal::HAL::get_instance().get_sorting_mechanism().get()->close();
		usleep(1000 * 500);

		std::cout << hal::HAL::get_instance().get_sorting_mechanism().get()->is_open() << std::endl;
		usleep(1000 * 500);
	}

	return 0;
	*/
}


#endif

