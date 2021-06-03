#include <logic/stm/StmRecieveWrpc/states/substm_running.h>
#include "error.h"
#include "idle.h"
#include "estop.h"
#include "service.h"

namespace logic {
namespace stm {
namespace top_level {

template<class T>
const std::string EStop<T>::name = "Error";
template<typename T>
std::string EStop<T>::get_name() { return name; }

template<typename T>
bool EStop<T>::rst_prs_srt(){
    if(_datamodel->get_estop_count() == 0){
        switch_state<Idle>();
        entry();
        return true;
    }
    return false;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
