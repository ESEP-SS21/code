#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {


class RecieveWrpcContext : public BaseContext {
public:
    RecieveWrpcContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;

};

}
}
}
