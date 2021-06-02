#pragma once

#include "../base_context.h"

namespace logic {
namespace stm {
namespace testStm {

class TestContext : public BaseContext {
public:
    TestContext(std::shared_ptr<IEventSender> eventSender);

    void handle(Event e) override;

};

}
}
}



