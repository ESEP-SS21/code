#include <logic/datamodel/unit_data.h>

#include <utility>

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

WorkpieceType UnitData::get_next_in_order() const {
    return _next_in_order;
}

std::shared_ptr<Workpiece> UnitData::get_pending_transfer() const {
    return _pending_transfer;
}

void UnitData::set_pending_transfer(std::shared_ptr<Workpiece> wrpc) {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _pending_transfer = std::move(wrpc);
}

bool UnitData::belt_empty() {
    return (get_start_height_sec()->workpiece_count() == 0)
            && (get_height_switch_sec()->workpiece_count() == 0)
            && (get_switch_end_sec()->workpiece_count() == 0);
}

} /* namespace datamodel */
} /* namespace logic */
