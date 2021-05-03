/*
 * BlinkWorker.cpp
 *
 *  Created on: 30.04.2021
 *      Author: jendr
 */

#include <../actuators/BlinkWorker.h>
#include <iostream>
#include <memory>

namespace hal {

BlinkWorker::BlinkWorker(std::shared_ptr<GPIOWrapper> gpio) :
		duty_cycle { 1000 }, running { true }, _gpio { gpio }, color { hal::RED } {
	blink_lock.try_lock();
}

void BlinkWorker::run() {
	int val = 0;
	while (running) {
		blink_lock.lock();
		blink_lock.unlock();
		val = !val;
		switch (color) {
		case GREEN:
			_gpio->out(gpio_adresses::BANK_ACTUATOR,
					gpio_adresses::AMPEL_GRUEN_1, val);
			break;
		case YELLOW:
			_gpio->out(gpio_adresses::BANK_ACTUATOR,
					gpio_adresses::AMPEL_GELB_1, val);
			break;
		default: // RED
			_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1,
					val);
			break;
		}

		usleep(duty_cycle * 500);
	}
}

void BlinkWorker::stop_loop() {
	stop_blinking();
	blink_lock.unlock();
	running = false;
}

void BlinkWorker::set_duty_cycle(const uint32_t milliseconds) {
	duty_cycle = milliseconds;
}

void BlinkWorker::start_blinking(Color c) {
	color = c;
	blink_lock.try_lock();
	blink_lock.unlock();
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, 0);
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, 0);
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 0);
}

void BlinkWorker::stop_blinking() {
	blink_lock.try_lock();
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, 0);
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, 0);
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 0);
}

BlinkWorker::~BlinkWorker() {
	running = false;
	blink_lock.try_lock();
	blink_lock.unlock();
}

} /* namespace hal */
