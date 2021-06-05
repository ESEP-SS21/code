#include "sub_operating.h"
#include "operating_substates/WaitingForWrpc.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

INIT_OPERATING_SUB_STM(SubOperating,WaitingForWrpc)

bool SubOperating::lb_sw_blck(){
    return false;
}
bool SubOperating::lb_ra_clr(){
    return false;
}
bool SubOperating::tim_alrt(int tim_id){
    return false;
}

void SubOperating::entry_history(){

}
void SubOperating::entry_wfstc(){

}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
