#pragma once

#include <memory>
#include "cb_section.h"
#include <array>

namespace logic {
namespace datamodel {

class UnitData {
public:
    virtual ~UnitData() = default;

    bool wrpc_fits_order(const Workpiece&) const;
    void wrpc_order_step();
    void wrpc_order_reset(WorkpieceType);

    std::shared_ptr<CBSection> get_switch_end_sec() const;
    std::shared_ptr<CBSection> get_height_switch_sec() const;
    std::shared_ptr<CBSection> get_start_height_sec() const;

    bool belt_is_blocked = false;
    bool ramp_full = false;
    std::shared_ptr<Workpiece> _pending_transfer = nullptr;

protected:
    const std::shared_ptr<CBSection> _switch_end_sec = std::make_shared<CBSection>();
    const std::shared_ptr<CBSection> _height_switch_sec = std::make_shared<CBSection>(
            _switch_end_sec);
    const std::shared_ptr<CBSection> _start_height_sec = std::make_shared<CBSection>(
            _start_height_sec);

    WorkpieceType _next_in_order = WorkpieceType(0);
    mutable std::mutex _unit_mutex;
};

} /* namespace datamodel */
} /* namespace logic */
