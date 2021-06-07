#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace operationManagerStm {


class OperationManagerContext : public BaseContext {
public:
    OperationManagerContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;
};

}
}
}
