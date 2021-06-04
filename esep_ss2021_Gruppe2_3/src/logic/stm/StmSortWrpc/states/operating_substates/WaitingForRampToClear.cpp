#include "WaitingForRampToClear.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(WaitingForRampToClear)

bool WaitingForRampToClear::tim_alrt(int payload){
    return false;
}

bool WaitingForRampToClear::lb_ra_clr(){
    return false;
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
