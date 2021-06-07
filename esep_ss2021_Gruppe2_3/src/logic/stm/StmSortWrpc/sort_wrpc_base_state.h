#pragma once

#include "../base_base_state.h"


namespace logic {
namespace stm {
namespace sortWrpcStm {

class SortWrpcBaseState : public BaseBaseState {

public:
    SortWrpcBaseState() = default;
    virtual bool lb_sw_blck(){return false;}
    virtual bool lb_sw_clr(){return false;}
    virtual bool lb_ra_clr(){return false;}
    virtual bool tim_alrt(int tim_id){return false;}
    virtual void entry(){}
    virtual void exit(){}

    virtual void entry_history(){}
    virtual void entry_wfstc(){}
    virtual void entry_discard(){}
    virtual void entry_waiting_for_ramp_to_clear(){}

    void init_sub_states() override;

    virtual bool has_super_exit_with_lb_sw_blck_from_waiting_for_wrpc() {return false;}
    virtual bool has_super_exit_with_lb_sw_blck_from_ramp_full() {return false;}
    virtual bool has_super_exit_with_lb_sw_clr() {return false;}
    virtual bool has_super_exit_with_tim_alrt() {return false;}

protected:
    bool _ramp_already_cleared = true;
    SortWrpcBaseState *_operating_substate {nullptr};
    SortWrpcBaseState *_wfstc_substate {nullptr};
};

}
}
}
