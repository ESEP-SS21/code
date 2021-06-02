#pragma once

#include "../base_context.h"
#include "logic/datamodel/unit_data.h"

namespace logic {
namespace stm {
namespace testStm {

#define _state std::dynamic_pointer_cast<TestBaseState>(_state)

class TestContext : public BaseContext {
public:
    TestContext(IEventSender* eventSender, UnitData* datamodel);

    void handle(Event e) override;

};

}
}
}



