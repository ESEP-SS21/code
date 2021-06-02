#pragma once

#include "../base_base_state.h"


namespace logic {
namespace stm {
namespace testStm {

class TestBaseState : public BaseBaseState {

public:
    TestBaseState() = default;

    virtual bool tick(int pa) { return false; }

protected:
    TestBaseState *_substate {nullptr};

    virtual void entry_sub_start_node() {}

};

}
}
}


