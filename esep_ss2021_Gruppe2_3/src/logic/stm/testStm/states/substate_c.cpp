#include "state_a.h"
#include "substate_c.h"

namespace logic {
namespace stm {
namespace testStm {

NAME(SubStateC)

bool SubStateC::tick(int pa) {
    _eventSender->send( { EventType::EVNT_ACK, pa, false });
    std::cout << "tick in C" << std::endl;
    return true;
}



}
}
}
