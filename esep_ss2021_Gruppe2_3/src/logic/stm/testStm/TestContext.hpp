#pragma once

#include <logic/stm/testStm/states/StateA.h>
#include "../base_context.hpp"

namespace logic {
namespace stm {
namespace testStm {

class TestContext : public BaseContext {
public:
    TestContext() : BaseContext(nullptr) {
//        std::shared_ptr<BaseBaseState> ptr2 = std::make_shared<StateA>();
//        BaseBaseState* ptr = static_cast<BaseBaseState*>(new StateA);
    }

    void handle(Event e) override {

    }
    std::string currentState(){
        return "asdf";
    }
};

}
}
}



