#include <logic/stm/StmWpTransfer/wp_transfer_states.h>

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
    if(_datamodel->_unit_type == UnitType::PRIMARY){
        _eventSender->send({EventType::EVNT_WRPC_TRNS_RQ, 0, true});
        exit();
        switch_state<NotBlocked>();
        entry();
    }
    if(_datamodel->_unit_type == UnitType::SECONDARY){
        //_datamodel->print_wrpc_data();
        //TODO: print_wrpc_data() implementieren
        exit();
        switch_state<Waiting>();
        entry();
    }
    return true;
}

bool NotBlocked::tim_alrt(int tim_id){
    Event e = Event::CreateTimer(TimerID::WRPC_TRANSFER_BLOCKED, 50, false);
        _eventSender->send(e);
    if(TimerID(tim_id) == TimerID::WRPC_TRANSFER_BLOCKED){
        _datamodel->_belt_blocked = true;
        exit();
        switch_state<Blocked>();
        entry();
    }
    return true;
}

bool NotBlocked::ack(){
    _eventSender->send({EventType::EVNT_ACK, 0, true});
    exit();
    switch_state<WaitingForWpToLeave>();
    entry();
    return true;
}

void Blocked::entry(){
    _eventSender->send({EventType::EVNT_ACT_BELT_STP, 0, true});
}

void Blocked::entry_history(){
    entry();
}

bool Blocked::ack(){
    _datamodel->_belt_blocked = false;
    _eventSender->send({EventType::EVNT_ACT_BELT_FWD, 0, true});
    exit();;
    switch_state<WaitingForWpToLeave>();
    entry();
}

bool WaitingForWpToLeave::tim_alrt(int tim_id){
    Event e = Event::CreateTimer(TimerID::WRPC_TRANSFER_BLOCKED, 2000, false);
        _eventSender->send(e);
    if(TimerID(tim_id) == TimerID::WRPC_TRANSFER_BLOCKED){
        _eventSender->send({EventType::EVNT_WRN, 0, true});
        if(warning == false){
            warning = true;
        }
        exit();
        switch_state<WaitingForWpToLeave>();
        entry();
    }
    return true;
}

bool WaitingForWpToLeave::lb_en_clr(){
    _datamodel->get_start_height_sec()->exit_first_workpiece();
    if(warning == true){
        _eventSender->send({EventType::EVNT_WRN_GONE, 0, true});
        warning = false;
    }
    exit();
    switch_state<WaitingForFinTransfer>();
    entry();
    return true;
}

bool WaitingForFinTransfer::tim_alrt(int tim_id){
    Event e = Event::CreateTimer(TimerID::WRPC_TRANSFER_BLOCKED, 500, false);
        _eventSender->send(e);
    if(TimerID(tim_id) == TimerID::WRPC_TRANSFER_BLOCKED){
        if(_datamodel->_belt_empty){
            _eventSender->send({EventType::EVNT_ACT_BELT_STP, 0, true});
        }
        exit();
        switch_state<Waiting>();
        entry();
    }
    return true;
}

} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
