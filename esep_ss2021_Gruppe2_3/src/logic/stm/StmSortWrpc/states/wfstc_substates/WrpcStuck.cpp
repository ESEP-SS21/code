#include "WrpcStuck.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(WrpcStuck)

void WrpcStuck::entry(){
    _eventSender->send( { EventType::EVNT_WRN, 0, false } );
}

void WrpcStuck::exit(){
    _eventSender->send( { EventType::EVNT_WRN_GONE, 0, false } );
}

bool WrpcStuck::has_super_exit_with_lb_sw_clr() {
    return true;;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
