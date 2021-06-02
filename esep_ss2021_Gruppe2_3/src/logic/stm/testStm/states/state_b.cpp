#include "state_b.h"
#include "state_c.h"

namespace logic {
namespace stm {
namespace testStm {

std::string StateB::get_name() {
    return _substate->get_name();
}

bool StateB::tick(int pa) {
    if (_substate->tick(pa))
        return true;

    _eventSender->send({EventType::EVNT_ACK, pa, false});
    std::cout << "tick" << std::endl;
    return true;
}

void StateB::entry_sub_start_node() {
    _substate = new StateC();
    _substate->SetData(_eventSender, _datamodel);
}

}
}
}
