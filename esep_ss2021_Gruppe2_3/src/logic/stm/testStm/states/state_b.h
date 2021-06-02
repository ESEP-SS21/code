#pragma once

#include <utility>

#include "../test_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class StateB : public TestBaseState {
public:
    bool tick(int pa) override;
    NAME_H

protected:
    void entry_sub_start_node() override;

};
}
}
}
