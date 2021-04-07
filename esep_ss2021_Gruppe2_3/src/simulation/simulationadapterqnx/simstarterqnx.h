/*
 * simstarterqnx.h
 *
 *  Created on: 11.04.2020
 *      Author: Lehmann
 */

#ifndef SRC_SIMSTARTER_H_
#define SRC_SIMSTARTER_H_

#include "simulation.h"
#include "simexecuter.h"
#include "simhci.h"
#include "simitemhandling.h"
#include "simqnxirqhandler.h"
#ifdef SIM_REPORT
#include "UDPSendersimreport.h"
#endif
#if defined(SIM_TWIN) || defined(SIM_MANUAL_START) || defined(SIM_EXT_CTRL)
#include "UDPConfigFileReader.h"
#include "UDPReceiverThreadSimItemHandling.h"
#include "UDPSendersim.h"
#include "simjsonmessagehandler.h"
#include "simctrlhandler.h"
#endif
#include <thread>

class SimulationStarterQNX {
private:
    bool simulationStarted = false;
    Simulation *sim = nullptr;
    SimulationExecuter *simrunner = nullptr;
    SimQNXIRQHandler *irqhandler = nullptr;
    SimItemHandling *handler;
    SimHCI *hci;
    thread *simrunnerthread = nullptr;
    thread *simirqthread = nullptr;
#ifdef SIM_REPORT
    UDPSenderSimReport* simreporthandling = nullptr;
#endif
#if defined(SIM_TWIN) || defined(SIM_REPORT) || defined(SIM_EXT_CTRL)
    UDPConfigFileReader *simudpconf = nullptr;
#endif
#if defined(SIM_TWIN) || defined(SIM_EXT_CTRL)
    UDPReceiverThreadSimItemHandling *simrecvitemhandling = nullptr;
    thread *simupdreceiverthread = nullptr;
    SimJSONMessageHandler *simjsonmh = nullptr;
    SimCtrlHandler *simctrlh = nullptr;
    UDPSenderSim* drophandler = nullptr;
#endif
public:
    SimulationStarterQNX();

    bool isStarted() {
        return simulationStarted;
    }
    unsigned long currentSimTime();
    void startSimulation();
};
extern SimulationStarterQNX *simulationStarter;

bool simulationStart();

#endif /* SRC_SIMSTARTER_H_ */
