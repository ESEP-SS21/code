#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace stm_service_mode {

class ServiceModeContext: public BaseContext {
public:
    ServiceModeContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;
};

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */

