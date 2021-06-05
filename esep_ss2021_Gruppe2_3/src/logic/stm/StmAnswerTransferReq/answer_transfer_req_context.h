#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace StmAnswerTransferReq {

class AnswerTransferReqContext: public BaseContext {
public:
    AnswerTransferReqContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;
};

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */

