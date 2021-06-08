#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace StmHeightMeasurement {

class HeightMeasurementContext: public BaseContext {
public:
    HeightMeasurementContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;
};

} /* namespace HeightMeasurement */
} /* namespace stm */
} /* namespace logic */
