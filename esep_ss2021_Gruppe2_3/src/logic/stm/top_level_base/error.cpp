#include "error.h"
#include "idle.h"
#include "estop.h"
#include "service.h"
#include "substm_running.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

STATE_INIT(Error)

template<T>
bool Error::estop_on(){
    switch_state<EStop>();
    entry();
    return true;
}

bool Error::all_err_gone(){
    switch_state<Running>();
    entry();
    entry_sub_running<>();
    return true;
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

