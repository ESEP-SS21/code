/*
 * unit_data.cpp
 *
 *  Created on: 21.05.2021
 *      Author: justi
 */

#include <logic/datamodel/unit_data.h>

namespace logic {
namespace datamodel {

UnitData::UnitData() {
    //switch_end_sec = std::make_shared<CBSection>();
    //height_switch_sec = std::make_shared<CBSection>(switch_end_sec);
    //start_height_sec = std::make_shared<CBSection>(height_switch_sec);
    _pending_transfer = nullptr;
}

UnitData::~UnitData() {

}

bool UnitData::wrpc_fits_order(const Workpiece& wrpc) const {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
}

void UnitData::wrpc_order_step() {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
}

void UnitData::wrpc_order_reset(WorkpieceType wrpc_type) {
    const std::lock_guard<std::mutex> lock(_unit_mutex);
}

} /* namespace datamodel */
} /* namespace logic */
