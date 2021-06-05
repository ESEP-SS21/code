#pragma once
#include "../../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
namespace sortWrpcStm {

class Discard: public SortWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool tim_alrt(int tim_id) override;

protected:
    void entry() override;

};

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
