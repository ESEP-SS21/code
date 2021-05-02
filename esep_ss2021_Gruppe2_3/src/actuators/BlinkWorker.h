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


namespace hal {

class BlinkWorker {
public:
	BlinkWorker();
	BlinkWorker(const BlinkWorker&);
	void run();
	void set_duty_cycle(const uint32_t milliseconds = 1000);
	void add_to_cycle();
	void start_blinking();
	void stop_blinking();
	void remove_from_cycle();
	void stop_loop();
	virtual ~BlinkWorker();
private:
	std::mutex blink_lock;
	useconds_t duty_cycle;
	bool running;
};

} /* namespace hal */

#endif /* SRC_ACTUATORS_BLINKWORKER_H_ */
