#pragma once

#include "../base_base_state.h"


namespace logic {
namespace stm {
namespace testStm {

class TestBaseState : public BaseBaseState {

public:
    virtual bool tick(int pa) { return false; }

protected:
    TestBaseState *_substate{static_cast<TestBaseState *>(calloc(1, sizeof(TestBaseState)))};

    virtual void entry_sub_start_node() {}

};

}
}
}


