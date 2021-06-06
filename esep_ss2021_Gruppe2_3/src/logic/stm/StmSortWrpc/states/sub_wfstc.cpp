#include "sub_wfstc.h"
#include "wfstc_substates/NoDiscard.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

INIT_WFSTC_SUB_STM(SubWfstc,NoDiscard)

bool SubWfstc::lb_sw_clr(){
    bool handled = _operating_substate->lb_sw_clr();
    if(!handled && _operating_substate->has_super_exit_with_lb_sw_clr_from_discard()){

    }
    if(!handled && _operating_substate->has_super_exit_with_lb_sw_clr_from_wrpc_stuck()){

    }
    return handled;
}

bool SubWfstc::tim_alrt(int tim_id){
    bool handled = _operating_substate->tim_alrt(tim_id);
    if(!handled && _operating_substate->has_super_exit_with_tim_alrt()){

    }
    return handled;
}
void SubWfstc::entry_discard(){

}

void SubWfstc::exit(){
    _eventSender->send( { EventType::EVNT_ACT_SORT_RST, 0, false } );
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
