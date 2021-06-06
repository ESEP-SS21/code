#include "sub_operating.h"
#include "operating_substates/WaitingForWrpc.h"
#include "sub_wfstc.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

INIT_OPERATING_SUB_STM(SubOperating,WaitingForWrpc)

bool SubOperating::lb_sw_blck(){
    bool handled = _operating_substate->lb_sw_blck();
    // WaitingForWrpc -> NoDiscard / Discard
    if(!handled && _operating_substate->has_super_exit_with_lb_sw_blck_from_waiting_for_wrpc()){
        Workpiece unchecked_wrpc = _datamodel->get_height_switch_sec()->first_workpiece();
        if(_datamodel->wrpc_fits_order(unchecked_wrpc)) { // in sorting order
            _operating_substate->exit();
            exit();
            new(this) SubWfstc;
            entry_sub_start_node();
        } else { // not in sorting order
            _operating_substate->exit();
            exit();
            new(this) SubWfstc;
            entry_discard();
        }
    }
    // RampFull -> NoDiscard
    if(!handled && _operating_substate->has_super_exit_with_lb_sw_blck_from_ramp_full()) {
        if(_datamodel->_unit_type == UnitType::PRIMARY) {
            _operating_substate->exit();
            exit();
            new(this) SubWfstc;
            entry_sub_start_node();
        }
    }
    return handled;
}

bool SubOperating::lb_ra_clr(){
    bool handled = _operating_substate->lb_ra_clr();
    return handled;
}

bool SubOperating::tim_alrt(int tim_id){
    bool handled = _operating_substate->tim_alrt(tim_id);
    return handled;
}

void SubOperating::entry_history(){
    _operating_substate->entry();
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
