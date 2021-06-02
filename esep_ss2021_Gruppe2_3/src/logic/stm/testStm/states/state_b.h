#pragma once

#include <utility>

#include "../test_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class StateB : public TestBaseState {
public:
    bool tick(int pa) override;

protected:
    void entry_sub_start_node() override;

public:

    static const std::string name;

    std::string get_name() override;

};
}
}
}
