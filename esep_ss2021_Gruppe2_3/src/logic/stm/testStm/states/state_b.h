#pragma once

#include <utility>

#include "../test_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class StateB : public TestBaseState {
public:
    Ctor(StateB);

    bool tick(int pa) override;

    static const std::string name;

};
}
}
}
