#include "state_a.h"
#include "sub_stm_b.h"

namespace logic {
namespace stm {
namespace testStm {

STATE_INIT(StateA)

bool StateA::tick(int pa) {
    _eventSender->send( { EventType::EVNT_ACK, pa, false });
    std::cout << "tick" << std::endl;
    new (this) SubStmB;
    entry_sub_start_node();
    return true;
}


}
}
}
