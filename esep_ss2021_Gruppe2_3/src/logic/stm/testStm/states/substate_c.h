#pragma once

#include <utility>

#include "../test_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class SubStateC : public TestBaseState {
public:
    bool tick(int pa) override;
    STATE_HEADER_INIT

};


}
}
}



