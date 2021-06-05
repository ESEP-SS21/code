#include "sub_wfstc.h"
#include "wfstc_substates/NoDiscard.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

INIT_WFSTC_SUB_STM(SubWfstc,NoDiscard)

bool SubWfstc::lb_sw_blck(){
    return false;
}
bool SubWfstc::lb_ra_clr(){
    return false;
}
bool SubWfstc::tim_alrt(int tim_id){
    return false;
}
void SubWfstc::entry_discard(){

}

void SubWfstc::exit(){
    _eventSender->send( { EventType::EVNT_ACT_SORT_RST, 0, false } );
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
