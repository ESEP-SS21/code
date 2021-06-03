#include <logic/stm/StmRecieveWrpc/states/substm_running.h>
#include "error.h"
#include "idle.h"
#include "estop.h"
#include "service.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

STATE_INIT(Idle)

bool Idle::estop_on(){
    switch_state<EStop>();
    entry();
    return true;
}

bool Idle::str_prs_srt(){
    switch_state<Running>();
    entry();
    entry_history();
    return true;
}

bool Idle::str_prs_lng(){
    switch_state<Service>();
    entry();
    return true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
