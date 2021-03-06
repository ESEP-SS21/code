#pragma once
#include "../../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

static constexpr int PASS_TIME_MS = 500;

class WaitingToPass: public SortWrpcBaseState {
public:
    STATE_HEADER_INIT

    bool has_super_exit_with_tim_alrt() override;

protected:
    void entry() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
