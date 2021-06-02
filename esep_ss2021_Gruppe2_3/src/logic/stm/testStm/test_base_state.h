#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class TestBaseState : public BaseBaseState {

public:
    TestBaseState(const std::string &name) : BaseBaseState(name) {};

    virtual bool tick() { return false; }

};

}
}
}


