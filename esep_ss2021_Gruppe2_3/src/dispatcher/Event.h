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
    int payload;
    bool broadcast;

    Event(EventType type, bool broadcast, int payload) :
            type(type), payload(payload), broadcast(broadcast) {
    }

    Event(const cnnMngmnt::header_t& header) :
            payload(header.value.sival_int), broadcast(false) {

        int evnt_id = header.code;
        if (transmission_bit_set(evnt_id)) {
            broadcast = true;
            evnt_id = mask_out_tranmission_bit(evnt_id);
        }
        type = EventType(evnt_id);
    }

    std::string str() {
        std::ostringstream buffer;
        buffer << type << " payload: " << payload;
        return buffer.str();
    }

private:
    bool transmission_bit_set(int evnt_id) {
        return (evnt_id & 0b01000000) != 0;
    }

    int mask_out_tranmission_bit(int evnt_id) {
        return evnt_id & (~0b01000000);
    }
};

struct EventSubscription {
    EventType type;
    cnnMngmnt::chid chid;
};

} /* namespace dispatcher */
