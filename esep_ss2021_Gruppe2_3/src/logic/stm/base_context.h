#pragma once

#include "dispatcher/Event.h"
#include <string>
#include "base_base_state.h"

namespace logic {
namespace stm {

using namespace dispatcher;

#define CONTEXT_CTOR(Type) \
Type::Type(IEventSender *eventSender, UnitData *datamodel) :\
    BaseContext() {\
    _state->SetData(eventSender, datamodel);\
}

template<typename EntryState>
class BaseContext {
public:

    BaseContext() : _state(new EntryState) {}

    virtual void handle(Event e) = 0;

    std::string currentState() {
        return _state->get_name();
    }

    std::string str() {
        return _state->str();
    }

    virtual ~BaseContext() {
        delete _state;
    };

protected:
    BaseBaseState *_state;
};

}
}
