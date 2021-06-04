#pragma once
#include "../recieve_wrpc_base_state.h"

namespace logic {
namespace stm {
// change namespace here
namespace recieveWrpcStm {

//change the base class of all states to your base state class
class Running: public RecieveWrpcBaseState {
public:
    SUBSTM_HEADER_INIT
    bool err() override;
    bool estop_on() override;
    bool stp_prs_srt() override;
    bool lb_st_blck() override;
    bool belt_stp() override;
    bool belt_fwd() override;
protected:
    void entry_sub_start_node() override;
    void entry_history() override;
};

class Idle : public RecieveWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool str_prs_srt() override;
    bool str_prs_lng() override;
};

class EStop: public RecieveWrpcBaseState {

public:
    STATE_HEADER_INIT
    bool rst_prs_srt() override;
};

class Error: public RecieveWrpcBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool all_err_gone() override;
};

class Service: public RecieveWrpcBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool srv_done() override;
};



} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
