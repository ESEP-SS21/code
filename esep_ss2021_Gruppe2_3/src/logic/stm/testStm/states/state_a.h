#pragma once

#include "../test_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class StateA : public TestBaseState {
public:
    StateA(std::shared_ptr<IEventSender> eventSender) : TestBaseState(name, eventSender) {}

    bool tick(int pa) override;

    static const std::string name;

};


}
}
}



