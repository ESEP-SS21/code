#pragma once

#include "../test_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class SubStmB : public TestBaseState {
public:
    bool tick(int pa) override;
    STATE_HEADER_INIT
    std::string str() override;


protected:
    void entry_sub_start_node() override;

};
}
}
}
