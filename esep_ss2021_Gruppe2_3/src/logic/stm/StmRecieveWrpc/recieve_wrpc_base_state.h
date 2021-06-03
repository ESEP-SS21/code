//#pragma once
//
//#include "../base_base_state.h"
//
//
//namespace logic {
//namespace stm {
//namespace top_level {
//
//class RecieveWrpcBaseState : public BaseBaseState {
//
//public:
//    RecieveWrpcBaseState() = default;
//
//    virtual bool lb_st_blck(){return false;}
//    virtual bool belt_stp(){return false;}
//    virtual bool belt_fwd(){return false;}
//    virtual bool str_prs_srt(){return false;}
//    virtual bool str_prs_lng(){return false;}
//    virtual bool stp_prs_srt(){return false;}
//    virtual bool rst_prs_srt(){return false;}
//    virtual bool estop_on(){return false;}
//    virtual bool err(){return false;}
//    virtual bool all_err_gone(){return false;}
//    virtual bool srv_done(){return false;}
//    virtual void entry(){}
//    virtual void exit(){}
//
//protected:
//    RecieveWrpcBaseState *_substate {nullptr};
//    virtual void entry_sub_start_node() {}
//    virtual void entry_history(){}
//
//};
//
//}
//}
//}
