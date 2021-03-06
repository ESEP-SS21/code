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
    bool hist_evnt() override;
    bool rst_to_srt() override;
protected:
    void exit() override;
    void entry_discard() override;
    void entry_wfstc() override;

};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
