#include "simqnxirqhandler.h"
#include "simqnxgpio.h"
#include "simqnxirq.h"

#include <iostream>
using namespace std;

SimQNXIRQHandler::SimQNXIRQHandler() {
	gpio = SimGPIO::getGPIO();
}

void SimQNXIRQHandler::operator()() {
	unsigned int inreg;

	// loop
	std::unique_lock<std::mutex> lock(runmutex);
	while (true) {
		cv.wait(lock); // wait on semaphore
		//cout << "unlocked " << timeStamp << endl;

		// transform bit pattern
		{
			std::lock_guard<std::mutex> lk(buffermutex);
			inreg = lastImage.in;
		}
		if (gpio->checkRasingIRQGPIO(inreg)) {
			// call ISR and Event as both could be set up.
			SimQNXIRQ::getSimIRQ()->raiseEventGPIO();
			SimQNXIRQ::getSimIRQ()->raiseISRGPIO();
#ifdef SIM_SHOW_ACTIONS
			cout << "<SIM> raise GPIO ISR" << endl;
#endif
		}
		if (gpio->checkRasingIRQADC()) {
			SimQNXIRQ::getSimIRQ()->raiseEventADC();
			SimQNXIRQ::getSimIRQ()->raiseISRADC();
#ifdef SIM_SHOW_ACTIONS
			cout << "<SIM> raise ADC ISR" << endl;
#endif
		}
	}
}

void SimQNXIRQHandler::cycleCompletedWith(unsigned long simulationtime,
		const SimulationIOImage &result, unsigned short int ADCRaw) {
	{
		std::lock_guard<std::mutex> lk(buffermutex);
		timeStamp = simulationtime;
		lastImage = result;
		lastADCRawValue = ADCRaw;
		gpio->updateDataADC(ADCRaw);
		//cout << "end:" << timeStamp << endl;
	}
	{
		//std::unique_lock < std::mutex > lock(runmutex);
		cv.notify_one();
	}
}
