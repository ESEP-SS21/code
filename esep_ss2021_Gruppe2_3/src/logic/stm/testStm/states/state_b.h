#pragma once

#include "../test_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class StateB : public TestBaseState {
public:
    StateB(std::shared_ptr<IEventSender> eventSender, std::shared_ptr<UnitData> datamodel) : TestBaseState(name, eventSender, datamodel) {}

    bool tick(int pa) override;

    static const std::string name;

};
}
}
}
