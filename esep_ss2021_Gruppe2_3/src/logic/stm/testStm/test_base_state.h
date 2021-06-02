#pragma once

#include "../base_base_state.h"

#define nextState(State) new(this) State(std::move(_eventSender), std::move(_datamodel))

namespace logic {
namespace stm {
namespace testStm {

class TestBaseState : public BaseBaseState {

public:
    TestBaseState(const std::string &name, std::shared_ptr<IEventSender> eventSender, std::shared_ptr<datamodel::UnitData> datamodel)
        : BaseBaseState(name, eventSender, datamodel) {};

    virtual bool tick(int pa) { return false; }

};

}
}
}


