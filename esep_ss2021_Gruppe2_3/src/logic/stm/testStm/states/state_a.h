#pragma once

#include "../test_base_state.h"
#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace testStm {

class StateA : public TestBaseState {
public:
    StateA(std::shared_ptr<IEventSender> eventSender) : TestBaseState("StateA", eventSender) {}

    bool tick(int pa) override {
        _eventSender->send({EventType::EVNT_ACK, pa, false});
        std::cout << "tick" << std::endl;
        return true;
    }
};


}
}
}



