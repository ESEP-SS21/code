
/* 
 * File:   simjsonmessagehandler.h
 * @author Lehmann
 * @date 15. Mai 2020
 */

#ifndef SIMJSONMESSAGEHANDLER_H
#define SIMJSONMESSAGEHANDLER_H
#include "simitemhandling.h"
#include "simctrlhandler.h"
#include "simhci.h"
#include "simjsonbase.h"
#include <string>

class SimJSONMessageHandler : public SimJSONBase {
private:
    std::string msgKey;
    std::string msgValue;
    SimItemHandling *itemhandler;
    SimCtrlHandler *simctrlhandler;
    SimHCI *hcihandler;
public:
    SimJSONMessageHandler(SimItemHandling *itemhandler, SimCtrlHandler *simctrl=nullptr, SimHCI *hcihandler=nullptr) : itemhandler(itemhandler), simctrlhandler(simctrl), hcihandler(hcihandler) {};
    bool dispatchMessage(std::string message);
    bool evalPair(const char* key, const char* value) override;
};


#endif /* SIMJSONMESSAGEHANDLER_H */

