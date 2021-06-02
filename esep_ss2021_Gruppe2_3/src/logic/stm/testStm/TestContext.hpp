#pragma once

#include "../base_context.hpp"

namespace logic {
namespace stm {
namespace testStm {

class TestContext : public BaseContext {
public:
    TestContext();
    void handle(Event e) override;
    std::string currentState();
};

}
}
}



