#include "WrpcStuck.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(WrpcStuck)

void WrpcStuck::entry(){

}

void WrpcStuck::exit(){

}

bool WrpcStuck::has_super_exit_with_lb_sw_clr() {
    return true;;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
