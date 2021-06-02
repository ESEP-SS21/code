#pragma once

#include "dispatcher/Event.h"
#include <string>
#include <logic/stm/testStm/states/state_a.h>
#include "base_base_state.h"

namespace logic {
namespace stm {

using namespace dispatcher;

class BaseContext {
public:

    BaseContext(logic::stm::testStm::StateA *state) : _state(state) {}

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
