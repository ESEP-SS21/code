/*
 * simqnxirqhandler.h
 *
 *  Created on: 18.04.2020
 *      Author: Lehmann
 */

#ifndef SRC_SIMULATION_SIMQNXIRQHANDLER_H_
#define SRC_SIMULATION_SIMQNXIRQHANDLER_H_

#include "simioimage.h"
#include "isimulationcycleendhandler.h"
#include <mutex>
#include <condition_variable>
#include "simqnxgpio.h"

class SimQNXIRQHandler : public ISimulationCycleEndHandler{
private:
	SimulationIOImage lastImage;
	unsigned long timeStamp = 0;
	unsigned short lastADCRawValue = 0;
	std::mutex buffermutex;
	std::mutex runmutex;
	std::condition_variable cv;
	SimGPIO* gpio;
public:
	SimQNXIRQHandler();
	virtual ~SimQNXIRQHandler(){};
	void operator()();
    void cycleCompletedWith(unsigned long simulationtime, const SimulationIOImage &result, unsigned short int ADCRaw) override;
};



#endif /* SRC_SIMULATION_SIMQNXIRQHANDLER_H_ */
