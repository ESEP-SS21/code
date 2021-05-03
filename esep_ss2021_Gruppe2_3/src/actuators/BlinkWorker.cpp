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
		_gpio { gpio }, _running { true }, _duty_cycle { 1000 }, _color { hal::RED } {
	_blink_lock.try_lock();
}

void BlinkWorker::run() {
	int val = 0;
	while (_running) {
		_blink_lock.lock();
		_blink_lock.unlock();
		val = !val;
		switch (_color) {
		case GREEN:
			_gpio->out(gpio_adresses::BANK_ACTUATOR,
					gpio_adresses::AMPEL_GRUEN_1, val);
			break;
		case YELLOW:
			_gpio->out(gpio_adresses::BANK_ACTUATOR,
					gpio_adresses::AMPEL_GELB_1, val);
			break;
		default:
			_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1,
					val);
			break;
		}

		std::this_thread::sleep_for (std::chrono::milliseconds(_duty_cycle/2));
	}
}

void BlinkWorker::stop_loop() {
	stop_blinking();
	_blink_lock.unlock();
	_running = false;
}

void BlinkWorker::set_duty_cycle(const uint32_t milliseconds) {
	_duty_cycle = milliseconds;
}

void BlinkWorker::start_blinking(Color c) {
	_color = c;
	_blink_lock.try_lock();
	_blink_lock.unlock();
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, 0);
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, 0);
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 0);
}

void BlinkWorker::stop_blinking() {
	_blink_lock.try_lock();
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, 0);
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, 0);
	_gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 0);
}

BlinkWorker::~BlinkWorker() {
	_running = false;
	_blink_lock.try_lock();
	_blink_lock.unlock();
}

} /* namespace hal */
