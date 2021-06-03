#include <logic/stm/StmRecieveWrpc/states/substm_running.h>
#include "error.h"
#include "idle.h"
#include "estop.h"
#include "service.h"

namespace logic {
namespace stm {
namespace recieveWrpcStm {

STATE_INIT(Service)

bool Service::estop_on(){
    switch_state<EStop>();
    entry();
    return true;
}

bool Service::srv_done(){
    switch_state<Idle>();
    entry();
    return true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
