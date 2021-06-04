#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {


class SortWrpcContext : public BaseContext {
public:
    SortWrpcContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;

};

}
}
}
