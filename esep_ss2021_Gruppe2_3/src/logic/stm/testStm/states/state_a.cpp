#include "state_a.h"
#include "state_b.h"

namespace logic {
namespace stm {
namespace testStm {

bool StateA::tick(int pa) {
    _eventSender->send( { EventType::EVNT_ACK, pa, false });
    std::cout << "tick" << std::endl;
    new (this) StateB;
    return true;
}

const std::string StateA::name = "StateA";

std::string StateA::get_name() {
    return name;
}

}
}
}
