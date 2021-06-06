#include "WrpcStuck.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(WrpcStuck)

void WrpcStuck::entry(){

}

void WrpcStuck::exit(){

}

bool WrpcStuck::has_super_exit_with_lb_sw_clr_from_wrpc_stuck() {
    return true;;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
