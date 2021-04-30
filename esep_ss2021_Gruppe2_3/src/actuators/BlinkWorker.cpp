/*
 * BlinkWorker.cpp
 *
 *  Created on: 30.04.2021
 *      Author: jendr
 */

#include <../actuators/BlinkWorker.h>
#include <iostream>

namespace hal {

BlinkWorker::BlinkWorker(): duty_cycle{1000}, running{true}{
	blink_lock.try_lock();
	active[0] = false;
	active[1] = false;
	active[2] = false;
}

void BlinkWorker::run(){
	while(running){

		blink_lock.lock();
		blink_lock.unlock();

		std::cout << "blink" << std::endl;

		usleep(duty_cycle*1000);
	}
	return;
}

void BlinkWorker::set_duty_cycle(const uint32_t milliseconds){
	duty_cycle = milliseconds;
}

void BlinkWorker::add_to_cycle(){

}

void BlinkWorker::remove_from_cycle(){

}

void BlinkWorker::start_blinking(){
	blink_lock.try_lock();
	blink_lock.unlock();
}

void BlinkWorker::stop_blinking(){
	blink_lock.lock();
}



BlinkWorker::~BlinkWorker() {

}

} /* namespace hal */
