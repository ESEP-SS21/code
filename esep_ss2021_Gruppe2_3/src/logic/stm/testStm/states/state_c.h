#pragma once

#include <utility>

#include "../test_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class StateC : public TestBaseState {
public:
    bool tick(int pa) override;
    NAME_H

};


}
}
}



