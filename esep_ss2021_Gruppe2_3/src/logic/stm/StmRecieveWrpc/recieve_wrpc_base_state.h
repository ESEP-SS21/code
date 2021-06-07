#pragma once

#include "../base_base_state.h"


namespace logic {
namespace stm {
namespace receiveWrpcStm {

class ReceiveWrpcBaseState : public BaseBaseState {

public:
    ReceiveWrpcBaseState() = default;

    virtual void entry() {}
    virtual void exit() {}
};

}
}
}
