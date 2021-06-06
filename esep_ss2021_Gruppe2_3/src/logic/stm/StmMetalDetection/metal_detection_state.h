#pragma once

#include "metal_detect_base_state.h"

namespace logic {
namespace stm {
namespace StmMetalDetection {

class MetalDetection: public MetalDetectionBaseState {
public:
    STATE_HEADER_INIT
    bool metal_dtc() override;
};


} /* namespace StmMetalDetection */
} /* namespace stm */
} /* namespace logic */
