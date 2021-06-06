#pragma once
#include "../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

class SubOperating: public SortWrpcBaseState {
public:
    SUBSTM_HEADER_INIT
    bool lb_sw_blck() override;
    bool lb_ra_clr() override;
    bool tim_alrt(int tim_id) override;
protected:
    void entry_history() override;
    void entry_waiting_for_ramp_to_clear() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
