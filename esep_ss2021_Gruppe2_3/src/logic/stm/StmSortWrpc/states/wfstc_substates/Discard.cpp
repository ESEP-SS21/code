#include "Discard.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(Discard)

void Discard::entry(){

}

bool Discard::tim_alrt(int tim_id){
    return false;
}

bool Discard::has_super_exit_with_lb_sw_clr_from_discard() {
    return true;
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
