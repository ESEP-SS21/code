#include <logic/stm/StmRecieveWrpc/states/substm_running.h>
#include "error.h"
#include "idle.h"
#include "estop.h"
#include "service.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

STATE_INIT(Error)

bool Error::estop_on(){
    new (this) EStop;
    entry();
    return true;
}

bool Error::all_err_gone(){
    new (this) Running;
    entry();
    entry_sub_start_node();
    return true;
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

