#include "WaitingToPass.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(WaitingToPass)

void WaitingToPass::entry(){
    //dispatcher::Event::CreateTimer(dispatcher::TimerID::, PASS_TIME_MS, false);
}

bool WaitingToPass::has_super_exit_with_tim_alrt() {
    return true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
