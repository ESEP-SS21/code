#include "state_a.h"
#include "state_c.h"

namespace logic {
namespace stm {
namespace testStm {

NAME(StateC)

bool StateC::tick(int pa) {
    _eventSender->send( { EventType::EVNT_ACK, pa, false });
    std::cout << "tick in C" << std::endl;
    return true;
}



}
}
}
