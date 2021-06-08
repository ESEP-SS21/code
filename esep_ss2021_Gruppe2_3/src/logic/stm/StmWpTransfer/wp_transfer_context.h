#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace StmWpTransfer {

class WpTransferContext: public BaseContext {
public:
    WpTransferContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;
};

} /* namespace StmWpTransfer */
} /* namespace stm */
} /* namespace logic */
