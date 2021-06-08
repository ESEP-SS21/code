#include <logic/stm/StmWpTransfer/wp_transfer_states.h>
#include <iostream>

namespace logic {
namespace stm {
namespace StmWpTransfer {

using namespace dispatcher;

STATE_INIT(Waiting)
STATE_INIT(NotBlocked)
STATE_INIT(Blocked)
STATE_INIT(WaitingForWpToLeave)
STATE_INIT(WaitingForFinTransfer)

bool Waiting::lb_en_blck() {
    if (_datamodel->_unit_type == UnitType::PRIMARY) {
        _eventSender->send( {EventType::EVNT_WRPC_TRNS_RQ,
                    _datamodel->get_switch_end_sec()->first_workpiece().encode().code , true});
        exit();
        switch_state<NotBlocked>();
        entry();
    }
    if (_datamodel->_unit_type == UnitType::SECONDARY) {
        _datamodel->get_switch_end_sec()->first_workpiece().print_wrpc_data();
        exit();
        switch_state<Waiting>();
        entry();
    }
    return true;
}

bool NotBlocked::tim_alrt(int tim_id) {
    bool handled = false;
    if (TimerID(tim_id) == TimerID::WRPC_TRANSFER_BLOCKED) {
        _datamodel->_belt_blocked = true;
        exit();
        switch_state<Blocked>();
        entry();
        handled = true;
    }
    return handled;
}

void NotBlocked::entry() {
    Event e = Event::CreateTimer(TimerID::WRPC_TRANSFER_BLOCKED, 50, false);
    _eventSender->send(e);

}

bool NotBlocked::ack() {
    exit();
    switch_state<WaitingForWpToLeave>();
    entry();
    return true;
}

void Blocked::entry() {
    _eventSender->send( { EventType::EVNT_ACT_BELT_STP, 0, false });
}

bool Blocked::ack() {
    _datamodel->_belt_blocked = false;
    _eventSender->send( { EventType::EVNT_ACT_BELT_FWD, 0, false });
    exit();
    switch_state<WaitingForWpToLeave>();
    entry();
    return true;
}


bool WaitingForWpToLeave::lb_en_clr() {
    _datamodel->get_switch_end_sec()->exit_first_workpiece();
    exit();
    switch_state<WaitingForFinTransfer>();
    entry();
    return true;
}

bool WaitingForFinTransfer::tim_alrt(int tim_id) {
    bool handled = false;
    if (TimerID(tim_id) == TimerID::WRPC_TRANSFER_LAST_REMAINING_WRPC) {
        if (_datamodel->belt_empty()) {
            _eventSender->send( { EventType::EVNT_ACT_BELT_STP });
        }
        exit();
        switch_state<Waiting>();
        entry();
        handled = true;
    }
    return handled;
}

void WaitingForFinTransfer::entry() {
    Event e = Event::CreateTimer(TimerID::WRPC_TRANSFER_LAST_REMAINING_WRPC, 500, false);
    _eventSender->send(e);
}

} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
