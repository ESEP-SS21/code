#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace StmErrorListener {


class ErrorListenerContext : public BaseContext {
public:
    ErrorListenerContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;

};
}
}
}
