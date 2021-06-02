#pragma once

#include "dispatcher/Event.h"
#include <string>
#include "base_base_state.h"

namespace logic {
namespace stm {

using namespace dispatcher;

class BaseContext {
public:

    BaseContext(std::shared_ptr<BaseBaseState> state) : _state(state) {}

    virtual void handle(Event e) = 0;

    std::string currentState() {
        return _state->get_name();
    }

    virtual ~BaseContext() = default;

protected:
    std::shared_ptr<BaseBaseState> _state;
};

}
}
