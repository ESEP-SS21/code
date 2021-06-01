#pragma once

#include "Event.h"

namespace dispatcher {

class IEventSender{
public:
    virtual void send(Event event, int prio=0) const = 0;
    virtual ~IEventSender() = default;
};

}

