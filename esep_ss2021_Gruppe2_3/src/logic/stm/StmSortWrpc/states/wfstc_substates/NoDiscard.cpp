#include "NoDiscard.h"
#include "WaitingToPass.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(NoDiscard)

void NoDiscard::entry(){
    _eventSender->send( { EventType::EVNT_ACT_SORT_NO_DSC, 0, false } );
}

bool NoDiscard::lb_sw_clr(){
    _datamodel->get_height_switch_sec()->transfer_first_workpiece();
    exit();
    switch_state<WaitingToPass>();
    entry();
    return true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
