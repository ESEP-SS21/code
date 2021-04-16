/* Simple demostration of the simulator usage
 * @author: Franz Korf
 * @author: Thomas Lehmann
 * @date: 2020-04-24
 */
#include <iostream>
#include "gpio_bbb.h"
#include "simqnxgpioapi.h" // must be last include !!!

using namespace std;

int main() {
	cout << "Switch traffic light on / off" << endl;

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

	return 0;
}

