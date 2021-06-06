#pragma once
#include "recieve_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace receiveWrpcStm {

class BeltNotRunning: public ReceiveWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
protected:
    void entry() override;
};


class BeltRunning: public ReceiveWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
protected:
    void entry() override;
};


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
