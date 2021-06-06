#include "WaitingToPass.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(WaitingToPass)

void WaitingToPass::entry(){

}

bool WaitingToPass::has_super_exit_with_tim_alrt() {
    return true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
