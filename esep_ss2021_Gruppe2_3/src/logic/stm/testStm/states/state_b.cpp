#include "state_b.h"
#include "state_a.h"
#include "state_c.h"

namespace logic {
namespace stm {
namespace testStm {

NAME(StateB)

bool StateB::tick(int pa) {
    //buggy, as _substate is never a nullptr
    if (_substate && _substate->tick(pa))
        return true;

    _eventSender->send({EventType::EVNT_ACK, pa, false});
    std::cout << "tick" << std::endl;
    entry_sub_start_node();
    return true;
}

void StateB::entry_sub_start_node() {
    new(_substate) StateC;
}

}
}
}
