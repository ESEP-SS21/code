#include "WaitingToPass.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(WaitingToPass)

using namespace ::dispatcher;

void WaitingToPass::entry(){
    Event e = Event::CreateTimer(TimerID::SORT_WRPC_NO_DISCARD_PASS, PASS_TIME_MS, false);
    _eventSender->send(e);
}

bool WaitingToPass::has_super_exit_with_tim_alrt() {
    return true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
