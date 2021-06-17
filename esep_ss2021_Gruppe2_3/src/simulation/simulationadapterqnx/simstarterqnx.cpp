/*
 * simstarter.cpp
 *
 *  Created on: 11.04.2020
 *      Author: Lehmann
 */
#include "simitemhandlingaction.h"
#include "simmasks.h"
#include "simbase.h"
#include "simqnxgpio.h"
#include "simstarterqnx.h"
#include <iostream>

using namespace std;

#ifndef GTEST
static bool simulationStarted = simulationStart();
#endif

SimulationStarterQNX *simulationStarter;

bool simulationStart() {
    static SimulationStarterQNX starter;
    simulationStarter = &starter;
    return starter.isStarted();
}

#if defined(SIM_TWIN_B) && !defined(SIM_TWIN)
#error System B defined without defining to be a Twin-system
#endif

SimulationStarterQNX::SimulationStarterQNX() {
#if defined(SIM_TWIN) || defined(SIM_REPORT) || defined(SIM_EXT_CTRL)
    // Sim HCI UDP support
    simudpconf = new UDPConfigFileReader(0, std::string("/simudp.conf"));
    simudpconf->showConfig();
#endif
#ifdef SIM_TWIN
    drophandler = new UDPSenderSim(*simudpconf);
#endif

    handler = new SimItemHandling();
    if (handler != nullptr) {
#ifndef SIM_TWIN_B
        /*
        handler->addAction(SimItemHandlingAction(5000, ItemKinds::flat));
        handler->addAction(
                SimItemHandlingAction(16000,
                        SimItemHandlingActionKind::removeallslide));
        handler->addAction(
                SimItemHandlingAction(16000,
                        SimItemHandlingActionKind::removeall));
        handler->addAction(SimItemHandlingAction(17000, ItemKinds::metalup));
        handler->addAction(
                SimItemHandlingAction(33000,
                        SimItemHandlingActionKind::removeall));
        handler->addAction(
            SimItemHandlingAction(33000,
                    SimItemHandlingActionKind::removeallslide));
        */
#else
    // add actions for system B here
#endif
    }

    hci = new SimHCI();
    if (hci != nullptr) {
#ifndef SIM_TWIN_B
    	/*
		hci->addAction(SimHCIAction(0));
		hci->addAction(SimHCIAction(3000, SimHCIActionKind::pressStartOnly));
		hci->addAction(SimHCIAction(3500, SimHCIActionKind::releaseAll));
		hci->addAction(SimHCIAction(35000, SimHCIActionKind::pressStartOnly));
		hci->addAction(SimHCIAction(36000, SimHCIActionKind::releaseAll));
		*/
#else
        // add actions for system B here
#endif
    }

#ifdef SIM_TWIN
    sim = new Simulation(handler, hci, drophandler);
#else
    sim = new Simulation(handler, hci);
#endif

    if (sim != nullptr) {
        simrunner = new SimulationExecuter(sim, 20);
        simrunnerthread = new thread(*simrunner);
    }
    simulationStarted = (sim != nullptr) && (simrunner != nullptr)
            && (simrunnerthread != nullptr);
    if (simulationStarted) {
        SimGPIO::getGPIO()->setSimulation(sim);
    }
    if (simulationStarted) {
        irqhandler = new SimQNXIRQHandler();
        simirqthread = new thread(std::ref(*irqhandler));
        sim->addCycleEndHandler(irqhandler);
    }
#ifdef SIM_REPORT
    simreporthandling = new UDPSenderSimReport(*simudpconf);
    sim->addReportHandler(simreporthandling);
#endif
#if defined(SIM_TWIN) || defined(SIM_EXT_CTRL)
    simctrlh = new SimCtrlHandler(sim);
    simjsonmh = new SimJSONMessageHandler(handler, simctrlh, hci);
    simrecvitemhandling = new UDPReceiverThreadSimItemHandling(*simudpconf, simjsonmh);
    simupdreceiverthread = new thread(std::ref(*simrecvitemhandling));
#endif
#ifdef SIM_TWIN
    sim->setDropHandler(drophandler);
#endif
    cout << "QNX-Sim (" << SimulationBase::simVersionCode << ") configuration "
            << (simulationStarted ? "completed" : "failed") << endl;
}

unsigned long SimulationStarterQNX::currentSimTime(){
    unsigned long result = 0;
    if(nullptr!=sim){
        result = sim->currentSimTime();
    }
    return result;
}

#if defined(SIM_MANUAL_START) && defined(SIM_TWIN_B)
#error Manual start is not allwoed for Twin-system B
#endif

void SimulationStarterQNX::startSimulation(){
    if(nullptr!=sim){
#if defined(SIM_MANUAL_START) && !defined(SIM_TWIN_B)
        sim->releaseSimulation();
#endif
    }
}
