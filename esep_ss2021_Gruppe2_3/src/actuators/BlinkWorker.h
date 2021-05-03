/*
 * BlinkWorker.h
 *
 *  Created on: 30.04.2021
 *      Author: jendr
 */

#ifndef SRC_ACTUATORS_BLINKWORKER_H_
#define SRC_ACTUATORS_BLINKWORKER_H_

#include <mutex>
#include <thread>
#include <../actuators/Color.h>
#include "../gpiowrapper.h"


namespace hal {

class BlinkWorker {
public:
	BlinkWorker(std::shared_ptr<GPIOWrapper>);
	BlinkWorker(const BlinkWorker&);
	void run();
	void set_duty_cycle(const uint32_t milliseconds = 1000);
	void start_blinking(Color);
	void stop_blinking();
	void stop_loop();
	virtual ~BlinkWorker();
private:
	std::shared_ptr<GPIOWrapper> _gpio;
	hal::Color color;
	std::mutex blink_lock;
	useconds_t duty_cycle;
	bool running;
};

} /* namespace hal */

#endif /* SRC_ACTUATORS_BLINKWORKER_H_ */
