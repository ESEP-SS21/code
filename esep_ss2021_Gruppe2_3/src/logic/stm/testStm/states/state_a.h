#pragma once

#include <utility>

#include "../test_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class StateA : public TestBaseState {
public:
    Ctor(StateA);

    bool tick(int pa) override;

    static const std::string name;

};


}
}
}



