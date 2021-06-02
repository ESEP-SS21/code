#include "sub_stm_b.h"
#include "substate_c.h"

namespace logic {
namespace stm {
namespace testStm {

INIT_SUB_STM(SubStmB, SubStateC)

bool SubStmB::tick(int pa) {
    if (_substate->tick(pa))
        return true;

    _eventSender->send({EventType::EVNT_ACK, pa, false});
    std::cout << "tick" << std::endl;
    return true;
}

}
}
}
