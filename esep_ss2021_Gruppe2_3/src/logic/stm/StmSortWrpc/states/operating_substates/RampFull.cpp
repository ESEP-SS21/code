#include "RampFull.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(RampFull)

bool RampFull::lb_sw_blck(){
    return false;
}

bool RampFull::lb_ra_clr(){
    return false;
}

void RampFull::exit(){

}

void RampFull::entry(){

}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
