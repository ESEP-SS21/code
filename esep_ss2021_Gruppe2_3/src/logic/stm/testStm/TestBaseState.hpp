#pragma once

#include <logic/stm/base_base_state.hpp>

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


