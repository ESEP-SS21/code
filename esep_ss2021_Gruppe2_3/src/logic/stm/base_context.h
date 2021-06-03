#pragma once

#include "dispatcher/Event.h"
#include <string>
#include <logic/stm/testStm/states/state_a.h>
#include "base_base_state.h"

namespace logic {
namespace stm {

using namespace dispatcher;

#define CONTEXT_CTOR(Type, StartState) \
Type::Type(IEventSender *eventSender, UnitData *datamodel) :\
    BaseContext(new StartState) {\
    _state->SetData(eventSender, datamodel);\
}

class BaseContext {
public:

    BaseContext(logic::stm::BaseBaseState *state) : _state(state) {}

    virtual void handle(Event e) = 0;

    std::string currentState() {
        return _state->get_name();
    }

    std::string str() {
        return _state->str();
    }

    virtual ~BaseContext() = default;

protected:
    BaseBaseState *_state;
};

}
}
