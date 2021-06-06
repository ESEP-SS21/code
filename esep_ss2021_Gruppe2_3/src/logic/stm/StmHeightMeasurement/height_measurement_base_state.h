#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace StmHeightMeasurement {

class StmHeightMeasurementBaseState: public BaseBaseState {
public:
    virtual bool lb_he_block(){return false;}
    virtual bool he_sensor_he(){};
    virtual bool lb_he_clear(){return false;}
    virtual bool wrpc_flp(){return false;}
};

} /* namespace StmHeightMeasurement */
} /* namespace stm */
} /* namespace logic */
