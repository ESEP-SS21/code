#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic
{
namespace stm {
namespace ServiceModeStm {


class ServiceModeContext : public BaseContext {
public:
    ServiceModeContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;

};

}
}
}
