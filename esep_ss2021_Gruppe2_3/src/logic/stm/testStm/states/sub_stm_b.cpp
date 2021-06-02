#include "sub_stm_b.h"
#include "substate_c.h"

namespace logic {
namespace stm {
namespace testStm {

std::string SubStmB::get_name() {
    return _substate->get_name();
}

bool SubStmB::tick(int pa) {
    if (_substate->tick(pa))
        return true;

    _eventSender->send({EventType::EVNT_ACK, pa, false});
    std::cout << "tick" << std::endl;
    return true;
}

void SubStmB::entry_sub_start_node() {
    _substate = new SubStateC();
    _substate->SetData(_eventSender, _datamodel);
}

}
}
}
