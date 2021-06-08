#include "WaitingForWrpc.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(WaitingForWrpc)

bool WaitingForWrpc::has_super_exit_with_lb_sw_blck_from_waiting_for_wrpc() {
    return true;
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
