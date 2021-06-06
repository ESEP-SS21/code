#pragma once
#include "recieve_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

class BeltNotRunning: public RecieveWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
protected:
    void entry() override;
};


class BeltRunning: public RecieveWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool handle(const Event &event) override;
protected:
    void entry() override;
};


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
