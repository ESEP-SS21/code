#pragma once

#include <string>
#include "cnnMngmnt/namespacedata"

namespace dispatcher {

enum class EventType{ SomeEvent = 0, AnotherEvent, Event12 = 12, Max = 63};

struct Event {
    EventType type;
    int payload;
};

struct EventSubscription {
    EventType type;
    cnnMngmnt::chid chid;
};

}
