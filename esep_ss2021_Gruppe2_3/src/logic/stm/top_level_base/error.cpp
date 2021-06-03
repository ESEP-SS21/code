#include "error.h"
#include "idle.h"
#include "estop.h"
#include "service.h"
#include "substm_running.h"

namespace logic {
namespace stm {
namespace top_level {

template<class T>
const std::string Error<T>::name = "Error";
template<typename T>
std::string Error<T>::get_name() { return name; }

template<typename T>
bool Error<T>::estop_on(){
    switch_state<EStop<T>>();
    entry();
    return true;
}

template<typename T>
bool Error<T>::all_err_gone(){
    switch_state<Running<T>>();
    entry();
    entry_sub_running();
    return true;
}


} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

