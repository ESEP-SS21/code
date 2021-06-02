#pragma once

#include "dispatcher/Event.h"
#include <string>
#include "base_base_state.hpp"

namespace logic {
namespace stm {
namespace testStm {

using namespace dispatcher;

class BaseContext {
public:

    BaseContext(std::shared_ptr<BaseBaseState> state) : _state(state) {}

    virtual void handle(Event e) = 0;

    virtual std::string currentState() = 0;

    virtual ~BaseContext() = default;

protected:
    std::shared_ptr<BaseBaseState> _state;
};

}
}
}
