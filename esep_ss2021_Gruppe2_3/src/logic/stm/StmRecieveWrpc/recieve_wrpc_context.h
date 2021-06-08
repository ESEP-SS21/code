#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace receiveWrpcStm {


class ReceiveWrpcContext : public BaseContext {
public:
    ReceiveWrpcContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;

};

}
}
}
