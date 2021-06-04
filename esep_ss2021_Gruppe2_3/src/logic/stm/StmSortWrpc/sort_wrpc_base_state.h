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

    virtual void entry_sub_start_node() {}
    virtual void entry_history(){}
    virtual void entry_wfstc(){}
    virtual void entry_discard(){}

protected:
    bool _ramp_already_cleared;
    SortWrpcBaseState *_substate {nullptr};
    SortWrpcBaseState *_operating_substate {nullptr};
    SortWrpcBaseState *_wfstc_substate {nullptr};
};

}
}
}
