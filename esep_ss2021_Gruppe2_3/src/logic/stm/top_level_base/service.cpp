#include "substm_running.h"
#include "error.h"
#include "idle.h"
#include "estop.h"
#include "service.h"

namespace logic {
namespace stm {
namespace top_level {

template<class T>
const std::string Service<T>::name = "Error";
template<typename T>
std::string Service<T>::get_name() { return name; }

template<typename T>
bool Service<T>::estop_on(){
    switch_state<EStop<T>>();
    entry();
    return true;
}

template<typename T>
bool Service<T>::srv_done(){
    switch_state<Idle<T>>();
    entry();
    return true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
