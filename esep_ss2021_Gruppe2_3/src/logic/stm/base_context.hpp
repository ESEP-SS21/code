#pragma once

#include "dispatcher/Event.h"

namespace logic {
namespace stm {

using namespace dispatcher;

class BaseContext {
public:
    virtual void handle(Event e) = 0;
};

}
}

