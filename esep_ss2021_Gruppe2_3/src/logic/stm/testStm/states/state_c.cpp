#include "state_a.h"
#include "state_c.h"

namespace logic {
namespace stm {
namespace testStm {

bool StateC::tick(int pa) {
    _eventSender->send( { EventType::EVNT_ACK, pa, false });
    std::cout << "tick" << std::endl;
    return true;
}

const std::string StateC::name = "StateA";

std::string StateC::get_name() {
    return name;
}
}
}
}
