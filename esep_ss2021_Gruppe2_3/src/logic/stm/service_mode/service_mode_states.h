#pragma once
#include "../base_base_state.h"

namespace logic {
namespace stm {
namespace ServiceModeStm {

enum class Step{
    first,
   s1_lb_st,
   DONE
};

class ServiceModeState: public BaseBaseState {
private:
    Step _currStep {Step::first};
    bool waiting_for_ack;
    void CheckForEndOfService();
    void step_done();

public:
    ServiceModeState() = default;
    STATE_HEADER_INIT
    bool handle(const Event &event) override;

    void handle_ack();
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
