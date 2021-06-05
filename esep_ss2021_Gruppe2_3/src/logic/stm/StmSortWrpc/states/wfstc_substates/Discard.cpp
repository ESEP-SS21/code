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

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
