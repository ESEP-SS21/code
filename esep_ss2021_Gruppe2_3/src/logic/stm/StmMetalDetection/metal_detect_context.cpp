#include <logic/stm/StmMetalDetection/metal_detect_context.h>
#include <logic/stm/StmMetalDetection/metal_detect_base_state.h>
#include <logic/stm/StmMetalDetection/metal_detection_state.h>

namespace logic {
namespace stm {
namespace StmMetalDetection {

//put the start state of your stm here
CONTEXT_CTOR(MetalDetectionContext, MetalDetection)

using namespace dispatcher;

void MetalDetectionContext::handle(Event e) {
    auto *state = (MetalDetectionBaseState *) (_state);
    if(_datamodel->_operating_mode != datamodel::OperatingMode::RUNNING){
        return;
    }
    switch (e.type) {
        case EventType::EVNT_SEN_METAL_DTC:
            state->metal_dtc();
            return;
        default:
            return;
    }
}

} /* namespace StmMetalDetection */
} /* namespace stm */
} /* namespace logic */
