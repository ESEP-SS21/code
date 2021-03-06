#include "sub_operating.h"
#include "operating_substates/WaitingForWrpc.h"
#include "sub_wfstc.h"
#include "operating_substates/WaitingForRampToClear.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

INIT_SUB_STM(SubOperating, WaitingForWrpc, _operating_substate)

bool SubOperating::lb_sw_blck() {
    bool handled = _operating_substate->lb_sw_blck();

    // Super Transition to Wfstc
    if (!handled) {
        //section cant be empty
        if(_datamodel->get_height_switch_sec()->workpiece_count() == 0) {
            _logger->error("MISSING WORKPIECE IN DATAMODEL");
            return handled;
        }
        Workpiece unchecked_wrpc = _datamodel->get_height_switch_sec()->first_workpiece();
        unchecked_wrpc.determine_type();
        if (_operating_substate->has_super_exit_with_lb_sw_blck_from_waiting_for_wrpc()) {
            // WaitingForWrpc -> NoDiscard
            if (_datamodel->wrpc_fits_order(unchecked_wrpc) && !unchecked_wrpc.is_flipped) { // in sorting order
                _operating_substate->exit();
                exit();
                switch_state<SubWfstc>();
                entry();
                entry_wfstc();
            // WaitingForWrpc -> Discard
            } else { // not in sorting order
                _operating_substate->exit();
                exit();
                switch_state<SubWfstc>();
                entry();
                entry_discard();
            }
        }
        // RampFull -> NoDiscard
        if (_operating_substate->has_super_exit_with_lb_sw_blck_from_ramp_full()) {
            if (_datamodel->_unit_type == UnitType::PRIMARY || (_datamodel->wrpc_fits_order(unchecked_wrpc) && !unchecked_wrpc.is_flipped)) {
                _operating_substate->exit();
                exit();
                switch_state<SubWfstc>();
                entry();
                entry_wfstc();
            }
        }
    }
    return handled;
}

bool SubOperating::hist_evnt(){
    entry();
    _operating_substate->entry();
    return true;
}

bool SubOperating::rst_to_srt(){
    entry();
    new(_operating_substate)WaitingForWrpc;
    _operating_substate->entry();
    return true;
}

bool SubOperating::lb_ra_clr() {
    bool handled = _operating_substate->lb_ra_clr();
    return handled;
}

bool SubOperating::tim_alrt(int tim_id) {
    bool handled = _operating_substate->tim_alrt(tim_id);
    return handled;
}

void SubOperating::entry_history() {
    _operating_substate->entry();
}

void SubOperating::entry_waiting_for_ramp_to_clear() {
    new (_operating_substate) WaitingForRampToClear;
    _operating_substate->entry();
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
