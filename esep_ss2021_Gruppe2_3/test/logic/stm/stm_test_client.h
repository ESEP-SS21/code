
#pragma once

#include "dispatcher/IEventSender.h"


using namespace dispatcher;
class StmTestClient : public IEventSender {
public:
    StmTestClient() {}

    void send(Event event, int prio) const override {
        std::cout << "send " << event.str() << std::endl;
    }

};



