#pragma once

#include <logic/stm/testStm/TestBaseState.hpp>
#include <logic/stm/base_base_state.hpp>

namespace logic {
namespace stm {
namespace testStm {

class StateA : public TestBaseState {
public:
    StateA() : TestBaseState("StateA"){}
    bool tick(){
        std::cout<<"tick"<<std::endl;
        return true;
    }
};


}
}
}



