#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace StmMetalDetection {

class MetalDetectionContext: public BaseContext {
public:
    MetalDetectionContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;
};

} /* namespace StmMetalDetection */
} /* namespace stm */
} /* namespace logic */

