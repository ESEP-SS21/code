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
