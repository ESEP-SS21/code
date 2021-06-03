#include <logic/stm/StmRecieveWrpc/states/substm_running.h>
#include "error.h"
#include "idle.h"
#include "estop.h"
#include "service.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

STATE_INIT(EStop)

bool EStop::rst_prs_srt(){
    if(_datamodel->get_estop_count() == 0){
        new (this) Idle;
        entry();
        return true;
    }
    return false;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
