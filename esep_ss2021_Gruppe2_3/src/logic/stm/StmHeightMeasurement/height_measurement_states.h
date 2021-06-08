#pragma once

#include "height_measurement_base_state.h"

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
    STATE_HEADER_INIT
    bool he_sensor_he(int payload) override;
    void entry() override;
};


} /* namespace HeightMeasurement */
} /* namespace stm */
} /* namespace logic */
