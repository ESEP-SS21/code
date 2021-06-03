#pragma once

#pragma once

#include "../base_base_state.h"


namespace logic {
namespace stm {

template <typename SubstateRunningStart>
class TopLevelBaseState : public BaseBaseState {

#define STATE_INIT_T(Type) \
const std::string Type::name = #Type;\
template<typename T>                \
std::string Type::get_name() {\
    return name;\
}

public:
    virtual bool lb_st_blck(){return false;}
    virtual bool belt_stp(){return false;}
    virtual bool belt_fwd(){return false;}
    virtual bool str_prs_srt(){return false;}
    virtual bool str_prs_lng(){return false;}
    virtual bool stp_prs_srt(){return false;}
    virtual bool rst_prs_srt(){return false;}
    virtual bool estop_on(){return false;}
    virtual bool err(){return false;}
    virtual bool all_err_gone(){return false;}
    virtual bool srv_done(){return false;}
    virtual void entry(){}
    virtual void exit(){}

protected:
    TopLevelBaseState *_substate_running;
    TopLevelBaseState *_substate_operating;
    TopLevelBaseState *_substate_waiting_for_switch_to_clear;
    virtual void entry_sub_running() {
        new (_substate_running) SubstateRunningStart;
        _substate_running->entry();
    }
    virtual void entry_history_sub_running(){}
    virtual void entry_sub_operating() {}
    virtual void entry_history_sub_operating(){}
    virtual void entry_sub_waiting_for_switch_to_clear() {}
    virtual void entry_history_sub_waiting_for_switch_to_clear(){}

};

}
}
