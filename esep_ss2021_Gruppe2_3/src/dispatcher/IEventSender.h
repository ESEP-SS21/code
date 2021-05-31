#pragma once

#include "Event.h"

namespace dispatcher {

class IEventSender{
public:
    virtual void send(Event event, int prio) const = 0;
    virtual ~IEventSender() = default;
};

}

