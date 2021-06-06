 #include <logic/stm/StmHeightMeasurement/height_measurement_context.h>
#include <logic/stm/StmHeightMeasurement/height_measurement_base_state.h>
#include "height_measurement_states.h"

namespace logic {
namespace stm {
namespace StmHeightMeasurement {

//put the start state of your stm here
CONTEXT_CTOR(HeightMeasurementContext, WaitingForWorkpiece)

using namespace dispatcher;

void HeightMeasurementContext::handle(Event e) {
    auto *state = (HeightMeasurementBaseState *) (_state);
    if(_datamodel->_operating_mode != datamodel::OperatingMode::RUNNING){
        return;
    }
}

} /* namespace StmHeightMeasurement */
} /* namespace stm */
} /* namespace logic */
