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
}

#else

//TODO blinken der Stoplight in Thread
//TODO XOR der SortingMechanisms in der HAL
//TODO Singleton Pattern der HAL funktioniert nicht, 'Malloc Check failed'

int main(int argc, char **argv) {


	auto hal_instance = hal::HAL::get_instance();
	while (1) {
		//CBMotor
		hal_instance.get_cb_motor().get()->set_direction(hal::FAST_FORWARDS);
		usleep(1000 * 500);

		hal_instance.get_cb_motor().get()->set_direction(hal::STOP);
		usleep(1000 * 500);

		hal_instance.get_cb_motor().get()->set_direction(hal::FAST_BACKWARDS);
		usleep(1000 * 500);

		hal_instance.get_cb_motor().get()->set_direction(hal::SLOW_BACKWARDS);
		usleep(1000 * 500);

		hal_instance.get_cb_motor().get()->set_direction(hal::SLOW_FORWARDS);
		usleep(1000 * 500);

		//SortingMechanism
		hal_instance.get_sorting_mechanism().get()->open();
		usleep(1000 * 500);

		std::cout << hal_instance.get_sorting_mechanism().get()->is_open() << std::endl;
		usleep(1000 * 500);

		hal_instance.get_sorting_mechanism().get()->close();
		usleep(1000 * 500);

		std::cout << hal_instance.get_sorting_mechanism().get()->is_open() << std::endl;
		usleep(1000 * 500);

		//Stoplight
		hal_instance.get_stoplight().get()->enable(hal::GREEN);
		usleep(1000 * 500);

		hal_instance.get_stoplight().get()->enable(hal::YELLOW);
		usleep(1000 * 500);

		hal_instance.get_stoplight().get()->enable(hal::RED);
		usleep(1000 * 500);

		hal_instance.get_stoplight().get()->disable(hal::GREEN);
		usleep(1000 * 500);

		hal_instance.get_stoplight().get()->disable(hal::YELLOW);
		usleep(1000 * 500);

		hal_instance.get_stoplight().get()->disable(hal::RED);
		usleep(1000 * 500);

		//LEDs
		hal_instance.get_leds().get()->enable(hal::START);
		usleep(1000 * 500);

		hal_instance.get_leds().get()->enable(hal::RESET);
		usleep(1000 * 500);

		hal_instance.get_leds().get()->enable(hal::Q1);
		usleep(1000 * 500);

		hal_instance.get_leds().get()->enable(hal::Q2);
		usleep(1000 * 500);

		hal_instance.get_leds().get()->disable(hal::START);
		usleep(1000 * 500);

		hal_instance.get_leds().get()->disable(hal::RESET);
		usleep(1000 * 500);

		hal_instance.get_leds().get()->disable(hal::Q1);
		usleep(1000 * 500);

		hal_instance.get_leds().get()->disable(hal::Q2);
		usleep(1000 * 500);
	}

	/*
	 * BEISPIELCODE
	 */
	/*
	 std::cout << "Switch traffic light on / off" << std::endl;

	 uintptr_t gpio_bank_1 = mmap_device_io(GPIO_SIZE,(uint64_t) GPIO_BASE_BANK1);
	 while (1) {
	 // very dirty
	 // register description:
	 // spruh73l.pdf page 4877
	 out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT), AMPEL_ROT_1); // set register
	 usleep(1000*500);

	 out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT), AMPEL_GELB_1); // set register
	 usleep(1000*500);

	 out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT), AMPEL_GRUEN_1); // set register
	 usleep(1000*1000);

	 out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT), AMPEL_ROT_1); // clear register
	 usleep(1000*500);

	 out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT), AMPEL_GELB_1); // clear register
	 usleep(1000*500);

	 out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT), AMPEL_GRUEN_1); // clear register
	 usleep(1000*1000);
	 }
	 */

	return 0;
}

#endif

