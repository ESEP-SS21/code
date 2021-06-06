#pragma once
#include "../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

class SubWfstc: public SortWrpcBaseState {
public:
    SUBSTM_HEADER_INIT
    bool lb_sw_clr() override;
    bool tim_alrt(int tim_id) override;
protected:
    void exit() override;
    void entry_discard() override;
};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
