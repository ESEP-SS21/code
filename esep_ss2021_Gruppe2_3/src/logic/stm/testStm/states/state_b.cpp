#include "state_b.h"
#include "state_a.h"

namespace logic {
namespace stm {
namespace testStm {

bool StateB::tick(int pa) {
    _eventSender->send( { EventType::EVNT_ACK, pa, false });
    std::cout << "tick" << std::endl;
    nextState(StateA);
    return true;
}

const std::string StateB::name = "StateB";

}
}
}
