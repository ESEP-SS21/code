#include "state_a.h"
#include "state_b.h"

namespace logic {
namespace stm {
namespace testStm {

bool StateA::tick(int pa) {
    _eventSender->send( { EventType::EVNT_ACK, pa, false });
    std::cout << "tick" << std::endl;
    nextState(StateB);
    return true;
}

const std::string StateA::name = "StateA";

}
}
}
