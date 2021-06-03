#include "error.h"
#include "idle.h"
#include "estop.h"
#include "service.h"
#include "substm_running.h"

namespace logic {
namespace stm {
namespace top_level {

template<class T>
const std::string Idle<T>::name = "Error";
template<typename T>
std::string Idle<T>::get_name() { return name; }

template<typename T>
bool Idle<T>::estop_on(){
    switch_state<EStop<T>>();
    entry();
    return true;
}

template<typename T>
bool Idle<T>::str_prs_srt(){
    switch_state<Running<T>>();
    entry();
    entry_history();
    return true;
}

template<typename T>
bool Idle<T>::str_prs_lng(){
    switch_state<Service<T>>();
    entry();
    return true;
}

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
