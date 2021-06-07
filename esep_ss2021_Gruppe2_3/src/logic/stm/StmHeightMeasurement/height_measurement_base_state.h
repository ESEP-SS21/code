#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace StmHeightMeasurement {

class HeightMeasurementBaseState: public BaseBaseState {
public:
    virtual void entry_history(){};
    virtual bool lb_he_block(){return false;}
    virtual bool he_sensor_he(int payload){};
    virtual bool wrpc_flp(){return false;}
    virtual void reset_to_start(){};
};

} /* namespace StmHeightMeasurement */
} /* namespace stm */
} /* namespace logic */
