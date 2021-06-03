#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace testStm {

//#define _state (TestBaseState)(_state)

class TestContext : public BaseContext<StateA> {
public:
    TestContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;

};

}
}
}



