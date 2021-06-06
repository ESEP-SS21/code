#pragma once

#include "dispatcher/Event.h"
#include <string>
#include "base_base_state.h"

namespace logic {
namespace stm {

using namespace dispatcher;

#define CONTEXT_CTOR(Type, StartState) \
Type::Type(IEventSender *eventSender, UnitData *datamodel) :\
    BaseContext(new StartState, datamodel, eventSender) {}

class BaseContext {
public:

    BaseContext( logic::stm::BaseBaseState *state, UnitData *datamodel, IEventSender *eventSender)
        : _state(state) , _datamodel(datamodel) {
        _state->SetData(eventSender, datamodel);
    }

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
    const UnitData* _datamodel;
};

}
}
