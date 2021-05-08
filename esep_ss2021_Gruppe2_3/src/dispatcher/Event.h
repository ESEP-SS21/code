#pragma once

#include <map>
#include <iostream>

#include "cnnMngmnt/namespacedata"

namespace dispatcher {

#define EVNT_PREFIX "EVNT_"

enum class EventType { //make sure to add a string representation for each value
    SomeEvent = 0, AnotherEvent, Event12, SIZE = 64
};

inline std::ostream& operator<<(std::ostream& out, const EventType& e) {
    static const std::string strs[static_cast<int>(EventType::SIZE)  + 1] = {
            "SomeEvent",
            "AnotherEvent",
            "AnotherEvent",
    };
    return std::cout << EVNT_PREFIX << strs[static_cast<int>(e)];
}


struct Event {
    EventType type;
    int payload;
};

struct EventSubscription {
    EventType type;
    cnnMngmnt::chid chid;
};

}
