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

    bool get_belt_blocked();
    bool get_ramp_full();
    std::shared_ptr<Workpiece> get_pending_transfer();
    int get_estop_count();
    int get_warning_count();

    void set_belt_blocked(bool);
    void set_ramp_full(bool);
    void set_pending_transfer(std::shared_ptr<Workpiece>);
    void set_estop_count(int);
    void set_warning_count(int);

    WorkpieceType get_next_in_order();

protected:
    const std::shared_ptr<CBSection> _switch_end_sec = std::make_shared<CBSection>();
    const std::shared_ptr<CBSection> _height_switch_sec = std::make_shared<CBSection>(
            _switch_end_sec);
    const std::shared_ptr<CBSection> _start_height_sec = std::make_shared<CBSection>(
            _height_switch_sec);

    bool _belt_blocked = false;
    bool _ramp_full = false;
    std::shared_ptr<Workpiece> _pending_transfer = nullptr;
    int _estop_count = 0;
    int _warning_count = 0;

    WorkpieceType _next_in_order = WorkpieceType::first_in_order();
    mutable std::mutex _unit_mutex;
};

} /* namespace datamodel */
} /* namespace logic */
