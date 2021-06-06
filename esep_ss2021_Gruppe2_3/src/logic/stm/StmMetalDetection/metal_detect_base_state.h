#pragma once

#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace StmMetalDetection {

class MetalDetectionBaseState: public BaseBaseState {
public:
    virtual bool metal_dtc(){return false;}
};

} /* namespace StmMetalDetection */
} /* namespace stm */
} /* namespace logic */
