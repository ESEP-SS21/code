#pragma once

#include <utility>

#include "../test_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class StateA : public TestBaseState {
public:
    StateA(std::shared_ptr<IEventSender> eventSender, std::shared_ptr<UnitData> datamodel)
        : TestBaseState(name, std::move(eventSender), std::move(datamodel)) {}

    bool tick(int pa) override;

    static const std::string name;

};


}
}
}



