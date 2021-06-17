#include "operation_manager_states.h"
#include "dispatcher/color.h"

namespace logic {
namespace stm {
namespace operationManagerStm {

#define UNRECOVERABLE_ESTOP_COUNT 3

using namespace dispatcher;

STATE_INIT(Running)

bool Running::estop_on() {
    exit();
    _datamodel->_estop_count = 1;
    switch_state<EStop>();
    entry();
    return true;
}

bool Running::conn_lost() {
    exit();
    _datamodel->_estop_count = UNRECOVERABLE_ESTOP_COUNT;
    switch_state<EStop>();
    entry();
    return true;
}

bool Running::stp_prs_srt() {
    exit();
    if(_datamodel->_warning_count == 0){
        _datamodel->_operating_mode = OperatingMode::IDLE;
        switch_state<Idle>();
    }else{
        _datamodel->_operating_mode = OperatingMode::ERROR;
        switch_state<GoneUnacknowledged>();
    }
    entry();
    return true;
}

bool Running::err() {
    _datamodel->_operating_mode = OperatingMode::ERROR;
    exit();
    switch_state<PendingUnacknowledged>();
    entry();
    return true;
}

bool Running::wrn() {
    _datamodel->_warning_count++;
    _eventSender->send({ EventType::EVNT_ACT_STPL_LED_BLNK_SLW, Color::YELLOW, false });
    return true;
}

bool Running::wrn_gone() {
    _datamodel->_warning_count--;
    if(_datamodel->_warning_count == 0){
        _eventSender->send({ EventType::EVNT_ACT_STPL_LED_ON, Color::GREEN, false });
    }
    return true;
}

void Running::entry() {
    _datamodel->_warning_count = 0;
    _eventSender->send({ EventType::EVNT_ACT_STPL_LED_ON, Color::GREEN, false });
}

void Running::exit() {
    _eventSender->send({ EventType::EVNT_ACT_BELT_STP, 0, false });
    _eventSender->send({ EventType::EVNT_ACT_SORT_RST, 0, false });
    _eventSender->send({ EventType::EVNT_ACT_STPL_LED_OFF, Color::GREEN, false });
}

STATE_INIT(Idle)

bool Idle::str_prs_srt() {
    exit();
    _datamodel->_operating_mode = OperatingMode::RUNNING;
    switch_state<Running>();
    if(_datamodel->_estop_triggered){
        _datamodel->_estop_triggered = false;
        _eventSender->send({EventType::EVNT_RST_TO_SRT});
    }else{
        _datamodel->_estop_triggered = false;
        _eventSender->send({EventType::EVNT_HIST});
    }
    entry();
    return true;
}

bool Idle::str_prs_lng() {
    exit();
    switch_state<Service>();
    _datamodel->_srv_pending = 1;
    entry();
    return true;
}


bool Idle::estop_on() {
    exit();
    _datamodel->_estop_count = 1;
    switch_state<EStop>();
    entry();
    return true;
}

bool Idle::conn_lost() {
    exit();
    _datamodel->_estop_count = UNRECOVERABLE_ESTOP_COUNT;
    switch_state<EStop>();
    entry();
    return true;
}

void Idle::entry() {
    _datamodel->_operating_mode = OperatingMode::IDLE;
    _eventSender->send({ EventType::EVNT_ACT_STPL_LED_ON, Color::YELLOW, false });
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_STR_LED_ON});
}

void Idle::exit() {
    _eventSender->send({ EventType::EVNT_ACT_STPL_LED_OFF, Color::YELLOW, false });
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_STR_LED_OFF});
}

STATE_INIT(EStop)

bool EStop::rst_prs_srt() {
    if(_datamodel->_estop_count == 0){
        exit();
        switch_state<Idle>();
        entry();
    }
    return true;
}

bool EStop::estop_on() {
    _datamodel->_estop_count++;
    return true;
}

bool EStop::estop_off() {
    _datamodel->_estop_count--;
    return true;
}

void EStop::entry(){
    int old_estop_count =_datamodel->_estop_count;
    if(!_datamodel->_estop_count == 0){
       new(_datamodel) UnitData(_datamodel->_unit_type);
    }
    _datamodel->_estop_count = old_estop_count;
    _datamodel->_estop_triggered = true;
    _datamodel->_operating_mode = OperatingMode::ESTOP;
    _eventSender->send({ EventType::EVNT_ACT_STPL_LED_BLNK_SLW, Color::RED, false });
    _eventSender->send({ EventType::EVNT_ACT_CTRL_T_RST_LED_ON});
    if(_datamodel->_estop_count>2){
        std::cout<< "FATAL ERROR" <<std::endl;
        std::cout<< "The Communication with the other System was interrupted or could not be established"<<std::endl;
        std::cout<< "Check the physical connection and make sure GNS is configured correctly"<<std::endl;
        std::cout<< "This error is irrecoverable and requires a restart to be solved"<<std::endl;
    }
}

void EStop::exit(){
    _eventSender->send({ EventType::EVNT_ACT_STPL_LED_OFF, Color::RED, false });
    _eventSender->send({ EventType::EVNT_ACT_CTRL_T_RST_LED_OFF});
}

STATE_INIT(PendingUnacknowledged)

bool PendingUnacknowledged::estop_on() {
    exit();
    _datamodel->_estop_count = 1;
    switch_state<EStop>();
    entry();
    return true;
}

bool PendingUnacknowledged::conn_lost() {
    exit();
    _datamodel->_estop_count = UNRECOVERABLE_ESTOP_COUNT;
    switch_state<EStop>();
    entry();
    return true;
}

bool PendingUnacknowledged::rst_prs_srt() {
    exit();
    switch_state<PendingAcknowledged>();
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_OFF});
    entry();
    return true;
}

bool PendingUnacknowledged::err_gone() {
    exit();
    switch_state<GoneUnacknowledged>();
    entry();
    return true;
}

void PendingUnacknowledged::entry() {
    _datamodel->_operating_mode = OperatingMode::ERROR;
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_ON});
    _eventSender->send({EventType::EVNT_ACT_STPL_LED_BLNK_FST, Color::RED});
}

STATE_INIT(PendingAcknowledged)

bool PendingAcknowledged::estop_on() {
    exit();
    _datamodel->_estop_count = 1;
    switch_state<EStop>();
    entry();
    return true;
}

bool PendingAcknowledged::conn_lost() {
    exit();
    _datamodel->_estop_count = UNRECOVERABLE_ESTOP_COUNT;
    switch_state<EStop>();
    entry();
    return true;
}

bool PendingAcknowledged::err_gone() {
    exit();
    switch_state<OK>();
    entry();
    return true;
}

void PendingAcknowledged::entry() {
    _eventSender->send({EventType::EVNT_ACT_STPL_LED_ON,Color::RED});
}

STATE_INIT(GoneUnacknowledged)

bool GoneUnacknowledged::estop_on() {
    exit();
    _datamodel->_estop_count = 1;
    switch_state<EStop>();
    entry();
    return true;
}

bool GoneUnacknowledged::conn_lost() {
    exit();
    _datamodel->_estop_count = UNRECOVERABLE_ESTOP_COUNT;
    switch_state<EStop>();
    entry();
    return true;
}

bool GoneUnacknowledged::rst_prs_srt() {
    exit();
    switch_state<OK>();
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_OFF});
    entry();
    return true;
}

void GoneUnacknowledged::entry() {
    _datamodel->_operating_mode = OperatingMode::ERROR;
    _eventSender->send({EventType::EVNT_ACT_STPL_LED_BLNK_SLW,Color::RED});
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_RST_LED_ON});
}

STATE_INIT(OK)

bool OK::estop_on() {
    exit();
    _datamodel->_estop_count = 1;
    switch_state<EStop>();
    entry();
    return true;
}

bool OK::conn_lost() {
    exit();
    _datamodel->_estop_count = UNRECOVERABLE_ESTOP_COUNT;
    switch_state<EStop>();
    entry();
    return true;
}

bool OK::str_prs_srt() {
    exit();
    _datamodel->_operating_mode = OperatingMode::RUNNING;
    _datamodel->_warning_count = 0;
    switch_state<Running>();
    entry();
    _eventSender->send({EventType::EVNT_HIST});
    return true;
}

void OK::entry() {
    _eventSender->send({EventType::EVNT_ACT_STPL_LED_OFF, Color::RED});
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_STR_LED_ON});
}

void OK::exit() {
    _eventSender->send({EventType::EVNT_ACT_CTRL_T_STR_LED_OFF});
}

STATE_INIT(Service)

void Service::entry() {
    _datamodel->_operating_mode = OperatingMode::SERVICE;
    _eventSender->send({EventType::EVNT_ACT_STPL_LED_BLNK_SLW,Color::GREEN});
}

bool Service::estop_on() {
    exit();
    _datamodel->_estop_count = 1;
    switch_state<EStop>();
    entry();
    return true;
}

bool Service::conn_lost(){
    exit();
    _datamodel->_estop_count = UNRECOVERABLE_ESTOP_COUNT;
    switch_state<EStop>();
    entry();
    return true;
}

bool Service::srv_done() {
    if(_datamodel->_srv_pending ==0){
        exit();
        switch_state<Idle>();
        entry();
    }else{
        _datamodel->_srv_pending--;
    }

    return true;
}

}
}
}
