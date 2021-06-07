#include "Discard.h"
#include "WrpcStuck.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(Discard)

void Discard::entry(){
    _eventSender->send( { EventType::EVNT_ACT_SORT_DSC, 0, false } );
    dispatcher::Event::CreateTimer(dispatcher::TimerID::SORT_WRPC_STUCK, SW_CLR_TIME_TOLERANCE_MS, false);
}

bool Discard::tim_alrt(int tim_id){
    bool handled = false;
    if(tim_id == static_cast<uint16_t>(dispatcher::TimerID::SORT_WRPC_STUCK)) {
        exit();
        switch_state<WrpcStuck>();
        entry();
        handled = true;
    }
    return handled;
}

bool Discard::has_super_exit_with_lb_sw_clr() {
    return true;
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
