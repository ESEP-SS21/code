#pragma once

#include "height_measurement_states.h"

namespace logic {
namespace stm {
namespace StmHeightMeasurement {

class WaitingForWorkpiece: public HeightMeasurementBaseState {
public:
    STATE_HEADER_INIT
    bool lb_he_blck() override;
};

class WaitingForHeight: public HeightMeasurementBaseState {
public:
    void he_sensor_he(int payload) override;
};

class WorkpiecePrimary: public HeightMeasurementBaseState {
public:
    bool lb_he_clr() override;
};

class WorkpieceSecondary: public HeightMeasurementBaseState {
public:
    bool lb_he_clr() override;
    bool wrpc_flp() override;
};

} /* namespace HeightMeasurement */
} /* namespace stm */
} /* namespace logic */
