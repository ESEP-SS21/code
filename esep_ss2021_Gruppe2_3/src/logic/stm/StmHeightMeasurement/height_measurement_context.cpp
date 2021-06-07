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
    switch (e.type) {
        case EventType::EVNT_SEN_LB_HE_BLCK:
            state->lb_he_block();
            return;
        case EventType::EVNT_HIST:
             state->entry_history();
             return;
        case EventType::EVNT_SEN_HEIGHT_HE:
            state->he_sensor_he(e.payload);
            return;
        case EventType::EVNT_RST_TO_SRT:
             state->reset_to_start();
             return;
        default:
            return;
    }
}

} /* namespace StmHeightMeasurement */
} /* namespace stm */
} /* namespace logic */
