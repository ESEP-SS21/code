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

	//hal::HAL* hal;
	while (1) {
		//hal->get_instance().get_cb_motor().get()->set_direction(hal::FAST_FORWARDS);
		std::cout << "FAST_FORWARD" << std::endl;
		usleep(1000 * 500);
		//hal->get_instance().get_cb_motor().get()->set_direction(hal::STOP);
		std::cout << "STOP" << std::endl;
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

