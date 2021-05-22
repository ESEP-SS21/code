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

protected:
    mutable std::mutex _unit_mutex;
};

} /* namespace datamodel */
} /* namespace logic */

#endif /* SRC_LOGIC_DATAMODEL_UNIT_DATA_H_ */
