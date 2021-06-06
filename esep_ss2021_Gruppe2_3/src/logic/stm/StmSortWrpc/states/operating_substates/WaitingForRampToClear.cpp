#include "WaitingForRampToClear.h"
#include "RampFull.h"
#include "WaitingForWrpc.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

static constexpr int RA_CLR_TIME_TOLERANCE_MS = 200;

STATE_INIT(WaitingForRampToClear)

bool WaitingForRampToClear::tim_alrt(int tim_id){
    if(tim_id == static_cast<uint16_t>(dispatcher::TimerID::SORT_WRPC_FULL)) {
        exit();
        new(_operating_substate) RampFull;
        entry();
    }
    return false;
}

bool WaitingForRampToClear::lb_ra_clr(){
    exit();
    new(_operating_substate) WaitingForWrpc;
    entry();
    return true;
}

void WaitingForRampToClear::entry() {
    if(_datamodel->_belt_empty) {
        _eventSender->send( { EventType::EVNT_ACT_BELT_STP, 0, false } );
    }
    dispatcher::Event::CreateTimer(dispatcher::TimerID::SORT_WRPC_FULL, RA_CLR_TIME_TOLERANCE_MS, false);
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
