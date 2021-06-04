#pragma once
#include "../sort_wrpc_base_state.h"

namespace logic {
namespace stm {
// change namespace here
namespace sortWrpcStm {

//change the base class of all states to your base state class
class Running: public SortWrpcBaseState {
public:
    SUBSTM_HEADER_INIT
    bool lb_sw_blck() override;
    bool lb_sw_clr() override;
    bool lb_ra_clr() override;
    bool tim_alrt(int tim_id) override;
    bool estop_on() override;
    bool stp_prs_srt() override;
    bool err() override;
protected:
    void entry_history() override;
};

class Idle : public SortWrpcBaseState {
public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool str_prs_srt() override;
    bool str_prs_lng() override;
};

class EStop: public SortWrpcBaseState {

public:
    STATE_HEADER_INIT
    bool rst_prs_srt() override;
};

class Error: public SortWrpcBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool all_err_gone() override;
    bool lb_ra_clr();
};

class Service: public SortWrpcBaseState {

public:
    STATE_HEADER_INIT
    bool estop_on() override;
    bool srv_done() override;
};



} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */
