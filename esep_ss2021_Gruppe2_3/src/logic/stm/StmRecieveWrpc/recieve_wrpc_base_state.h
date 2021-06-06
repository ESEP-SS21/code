#pragma once

#include "../base_base_state.h"


namespace logic {
namespace stm {
namespace recieveWrpcStm {

class RecieveWrpcBaseState : public BaseBaseState {

public:
    RecieveWrpcBaseState() = default;

    virtual void entry() {}
    virtual void exit() {}
};

}
}
}
