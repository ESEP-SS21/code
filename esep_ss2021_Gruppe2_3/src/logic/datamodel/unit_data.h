#pragma once

#include <memory>
#include "cb_section.h"
#include <array>

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
    bool get_belt_empty();

    void set_belt_blocked(bool);
    void set_ramp_full(bool);
    void set_pending_transfer(std::shared_ptr<Workpiece>);
    void set_estop_count(int);
    void set_warning_count(int);
    void set_belt_empty(bool);

    UnitType get_unit_type();
    void set_unit_type(UnitType unit_type);
    OperatingMode get_operating_mode();
    void set_operating_mode(OperatingMode mode);
    BeltState get_belt_state();
    void set_belt_state(BeltState state);
    SorterState get_sorter_state();
    void set_sorter_state(SorterState state);
    WorkpieceType get_next_in_order();

private:
    const std::shared_ptr<CBSection> _switch_end_sec = std::make_shared<CBSection>();
    const std::shared_ptr<CBSection> _height_switch_sec = std::make_shared<CBSection>(
            _switch_end_sec);
    const std::shared_ptr<CBSection> _start_height_sec = std::make_shared<CBSection>(
            _height_switch_sec);

    OperatingMode _operating_mode;
    const UnitType _unit_type;

    bool _belt_empty = true;
    bool _belt_blocked = false;
    bool _ramp_full = false;
    std::shared_ptr<Workpiece> _pending_transfer = nullptr;
    int _estop_count = 0;
    int _warning_count = 0;

    OperatingMode _mode = OperatingMode::IDLE;

    // to save the state when reentering running mode from error
    BeltState _belt_state = BeltState::STOP;
    SorterState _sorter_state = SorterState::NOTSET;

    WorkpieceType _next_in_order = WorkpieceType::first_in_order();
    mutable std::mutex _unit_mutex;
};

} /* namespace datamodel */
} /* namespace logic */
