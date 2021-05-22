/*
 * unit_data.h
 *
 *  Created on: 21.05.2021
 *      Author: justi
 */

#ifndef SRC_LOGIC_DATAMODEL_UNIT_DATA_H_
#define SRC_LOGIC_DATAMODEL_UNIT_DATA_H_

#include <memory>
#include "cb_section.h"

namespace logic {
namespace datamodel {

class UnitData {
public:
    bool belt_is_blocked;
    bool ramp_full;
    std::shared_ptr<Workpiece> _pending_transfer;

    UnitData();
    virtual ~UnitData();

    bool wrpc_fits_order(const Workpiece&) const;
    void wrpc_order_step();
    void wrpc_order_reset(WorkpieceType);

    std::shared_ptr<CBSection> get_switch_end_sec() const;
    std::shared_ptr<CBSection> get_height_switch_sec() const;
    std::shared_ptr<CBSection> get_start_height_sec() const;

protected:
    const std::shared_ptr<CBSection> switch_end_sec = std::make_shared<CBSection>();
    const std::shared_ptr<CBSection> height_switch_sec = std::make_shared<CBSection>(switch_end_sec);
    const std::shared_ptr<CBSection> start_height_sec = std::make_shared<CBSection>(height_switch_sec);

    WorkpieceType _next_in_order = WorkpieceType::WRPC_HM;
    mutable std::mutex _unit_mutex;
};

} /* namespace datamodel */
} /* namespace logic */

#endif /* SRC_LOGIC_DATAMODEL_UNIT_DATA_H_ */
