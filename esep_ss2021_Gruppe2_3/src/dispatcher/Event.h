#pragma once

#include <map>
#include <iostream>
#include <sstream>

#include "cnnMngmnt/namespacedata"

namespace dispatcher {

#define EVNT_PREFIX "EVNT_"

enum class EventType { //make sure to add a string representation for each value
    SomeEvent = 0, AnotherEvent, Event12, SIZE = 64
};

inline std::ostream& operator<<(std::ostream& out, const EventType& e) {
    static const std::string strs[static_cast<int>(EventType::SIZE) + 1] = { "SomeEvent",
            "AnotherEvent", "Event12", };
    return out << EVNT_PREFIX << strs[static_cast<int>(e)];
}

inline std::string str(EventType et) {
    std::ostringstream buffer;
    buffer << et;
    return buffer.str();
}

struct Event {
    EventType type;
    bool broadcast;
    int payload;

    Event(EventType type, bool broadcast, int payload) :
            type(type), broadcast(broadcast), payload(payload) {
    }

    Event(const cnnMngmnt::header_t& header, bool broadcast) :
            type(EventType(header.code)), broadcast(broadcast), payload(header.value.sival_int) {
    }

    std::string str() {
        std::ostringstream buffer;
        buffer << type << " payload: " << payload;
        return buffer.str();
    }

};

struct EventSubscription {
    EventType type;
    cnnMngmnt::chid chid;
};

}
