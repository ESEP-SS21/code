#include <logic/datamodel/unit_data.h>

namespace logic {
namespace datamodel {

UnitData::UnitData(UnitType unit_type) : _unit_type(unit_type) {

}

bool UnitData::wrpc_fits_order(const Workpiece& wrpc) const {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    return wrpc.get_type() == this->_next_in_order;
}

void UnitData::wrpc_order_step() {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _next_in_order = _next_in_order.next_in_sorting_order();
}

void UnitData::wrpc_order_reset(WorkpieceType wrpc_type) {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _next_in_order = wrpc_type;
}

std::shared_ptr<CBSection> UnitData::get_switch_end_sec() const {
    return _switch_end_sec;
}

std::shared_ptr<CBSection> UnitData::get_height_switch_sec() const {
    return _height_switch_sec;
}

std::shared_ptr<CBSection> UnitData::get_start_height_sec() const {
    return _start_height_sec;
}

WorkpieceType UnitData::get_next_in_order() {
    return _next_in_order;
}

bool UnitData::get_belt_blocked() {
    return _belt_blocked;
}

bool UnitData::get_ramp_full() {
    return _ramp_full;
}

std::shared_ptr<Workpiece> UnitData::get_pending_transfer() {
    return _pending_transfer;
}

int UnitData::get_estop_count() {
    return _estop_count;
}

int UnitData::get_warning_count() {
    return _warning_count;
}

bool UnitData::get_belt_empty() {
    return _belt_empty;
}

void UnitData::set_belt_blocked(bool val) {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _belt_blocked = val;
}

void UnitData::set_ramp_full(bool val) {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _ramp_full = val;
}

void UnitData::set_pending_transfer(std::shared_ptr<Workpiece> wrpc) {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _pending_transfer = wrpc;
}

void UnitData::set_estop_count(int val) {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _estop_count = val;
}

void UnitData::set_warning_count(int val) {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _warning_count = val;
}

void UnitData::set_operating_mode(OperatingMode mode){
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _mode = mode;
}

OperatingMode UnitData::get_operating_mode(){
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    return _mode;
}

void UnitData::set_belt_state(BeltState state){
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _belt_state = state;
}

BeltState UnitData::get_belt_state(){
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    return _belt_state;
}

void UnitData::set_sorter_state(SorterState state){
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _sorter_state = state;
}

SorterState UnitData::get_sorter_state(){
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    return _sorter_state;
}

void UnitData::set_belt_empty(bool val) {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _belt_empty = val;
}



} /* namespace datamodel */
} /* namespace logic */
