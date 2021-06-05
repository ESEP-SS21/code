#include "NoDiscard.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

STATE_INIT(NoDiscard)

void NoDiscard::entry(){

}

bool NoDiscard::lb_sw_clr(){
    return false;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
