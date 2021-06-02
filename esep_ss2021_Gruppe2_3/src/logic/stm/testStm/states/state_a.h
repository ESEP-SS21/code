#pragma once

#include "../test_base_state.h"
#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class StateA : public TestBaseState {
public:
    StateA() : TestBaseState("StateA") {}

    bool tick() {
        std::cout << "tick" << std::endl;
        return true;
    }
};


}
}
}



