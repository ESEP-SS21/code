#pragma once

#include <memory>
#include "cb_section.h"
#include <array>
#include <atomic>

namespace logic {
namespace datamodel {

enum class UnitType{
    PRIMARY,
    SECONDARY,
};

enum class OperatingMode{
    IDLE,
    RUNNING,
    ERROR,
    ESTOP,
    SERVICE,
};

enum class SorterState{
    NOTSET,
    DISCARD,
    NODISCARD,
};

enum class BeltState{
    STOP,
    RUNNING,
};

class UnitData {
public:
    UnitData(UnitType unit_type);
    virtual ~UnitData() = default;

    std::shared_ptr<CBSection> get_switch_end_sec() const;
    std::shared_ptr<CBSection> get_height_switch_sec() const;
    std::shared_ptr<CBSection> get_start_height_sec() const;
    std::shared_ptr<Workpiece> get_pending_transfer() const;
    WorkpieceType get_next_in_order() const;
    void set_pending_transfer(std::shared_ptr<Workpiece>);
    bool wrpc_fits_order(const Workpiece&) const;
    void wrpc_order_step();
    void wrpc_order_reset(WorkpieceType);

    std::atomic<bool> _belt_blocked{false};
    std::atomic<bool> _belt_empty{true};
    std::atomic<bool> _ramp_full{false};
    std::atomic<int> _estop_count{0};
    std::atomic<int> _warning_count{0};
    const UnitType _unit_type;
    std::atomic<OperatingMode> _operating_mode {OperatingMode::IDLE};
    std::atomic<BeltState> _belt_state {BeltState::STOP};
    std::atomic<SorterState> _sorter_state {SorterState::NOTSET};

private:
    const std::shared_ptr<CBSection> _switch_end_sec = std::make_shared<CBSection>();
    const std::shared_ptr<CBSection> _height_switch_sec = std::make_shared<CBSection>(
            _switch_end_sec);
    const std::shared_ptr<CBSection> _start_height_sec = std::make_shared<CBSection>(
            _height_switch_sec);
    std::shared_ptr<Workpiece> _pending_transfer = nullptr;

    WorkpieceType _next_in_order = WorkpieceType::first_in_order();
    mutable std::mutex _unit_mutex;
};

} /* namespace datamodel */
} /* namespace logic */
