#include "state_b.h"
#include "state_a.h"

namespace logic {
namespace stm {
namespace testStm {

bool StateB::tick(int pa) {
    _eventSender->send( { EventType::EVNT_ACK, pa, false });
    std::cout << "tick" << std::endl;
    new (this) StateA(std::move(_eventSender), std::move(_datamodel));
    return true;
}

const std::string StateB::name = "StateB";

}
}
}
