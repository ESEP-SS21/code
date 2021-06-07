#include "sub_wfstc.h"
#include "wfstc_substates/NoDiscard.h"
#include "sub_operating.h"
#include "wfstc_substates/Discard.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

INIT_WFSTC_SUB_STM(SubWfstc, NoDiscard)

bool SubWfstc::lb_sw_clr() {
    bool handled = _wfstc_substate->lb_sw_clr();
    if (!handled && _wfstc_substate->has_super_exit_with_lb_sw_clr()) {
        _datamodel->get_height_switch_sec()->exit_first_workpiece();
        _wfstc_substate->exit();
        exit();
        new (this) SubOperating;
        entry();
        entry_waiting_for_ramp_to_clear();
    }
    return handled;
}

bool SubWfstc::tim_alrt(int tim_id) {
    bool handled = _wfstc_substate->tim_alrt(tim_id);
    if (tim_id == static_cast<uint32_t>(dispatcher::TimerID::SORT_WRPC_NO_DISCARD_PASS)) {
        if (!handled && _wfstc_substate->has_super_exit_with_tim_alrt()) {
            _wfstc_substate->exit();
            exit();
            new (this) SubOperating;
            entry();
            entry_history();
        }
    }
    return handled;
}
void SubWfstc::entry_discard() {
    new (_wfstc_substate) Discard;
    _wfstc_substate->entry();
}

void SubWfstc::entry_wfstc() {
    new (_wfstc_substate) NoDiscard;
    _wfstc_substate->entry();
}

void SubWfstc::exit() {
    _eventSender->send( { EventType::EVNT_ACT_SORT_RST, 0, false });
}
;

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
