#include <logic/datamodel/unit_data.h>

namespace logic {
namespace datamodel {

bool UnitData::wrpc_fits_order(const Workpiece& wrpc) const {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    return wrpc.type == this->_next_in_order;
}

void UnitData::wrpc_order_step() {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
    _next_in_order =
            (_next_in_order == WorkpieceType::WRPC_HM) ? WorkpieceType::WRPC_HB :
            (_next_in_order == WorkpieceType::WRPC_HB) ?
                    WorkpieceType::WRPC_L : WorkpieceType::WRPC_HM;
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

} /* namespace datamodel */
} /* namespace logic */
