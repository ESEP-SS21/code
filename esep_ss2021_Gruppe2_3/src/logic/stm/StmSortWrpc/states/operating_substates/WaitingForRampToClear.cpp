#include "WaitingForRampToClear.h"
#include "RampFull.h"
#include "WaitingForWrpc.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(WaitingForRampToClear)

using namespace ::dispatcher;

bool WaitingForRampToClear::tim_alrt(int tim_id){
    bool handled = false;
    if(TimerID(tim_id) == TimerID::SORT_WRPC_FULL) {
        exit();
        switch_state<RampFull>();
        entry();
        handled = true;
    }
    return handled;
}

bool WaitingForRampToClear::lb_ra_clr(){
    exit();
    switch_state<WaitingForWrpc>();
    entry();
    return true;
}

void WaitingForRampToClear::entry() {
    if(_datamodel->_belt_empty) {
        _eventSender->send( { EventType::EVNT_ACT_BELT_STP, 0, false } );
    }
    Event e = Event::CreateTimer(TimerID::SORT_WRPC_FULL, RA_CLR_TIME_TOLERANCE_MS, false);
    _eventSender->send(e);
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
