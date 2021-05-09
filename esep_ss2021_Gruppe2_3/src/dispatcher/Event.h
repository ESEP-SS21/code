#pragma once

#include <map>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp> //todo move this to cpp as this is a 25k line include

#include "cnnMngmnt/namespacedata"

namespace dispatcher {

#define EVNT_PREFIX "EVNT_"

enum class EventType { //make sure to add a string representation for each value
    SomeEvent = 0, AnotherEvent, Event12, SIZE = 64
};

inline std::ostream& operator<<(std::ostream& out, const EventType& e) {
    static const std::string strs[static_cast<int>(EventType::SIZE) + 1] = { "SomeEvent",
            "AnotherEvent", "Event12", };
    return out << strs[static_cast<int>(e)];
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
        if ((evnt_id & 0b01000000) != 0) {
            broadcast = true;
            // mask out transmission bit
            evnt_id = evnt_id & (~0b01000000);
        }
        type = EventType(evnt_id);
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

using nlohmann::json;

inline void to_json(json& j, const Event& e) {
    j = json{{"EVNT", str(e.type)}, {"PAYL", e.payload}};
}

inline void from_json(const json& j, Event& e) { //TODO make this work
    j.at("EVNT").get_to(e.type);
    j.at("PAYL").get_to(e.payload);
    e.broadcast = false;
}

}
