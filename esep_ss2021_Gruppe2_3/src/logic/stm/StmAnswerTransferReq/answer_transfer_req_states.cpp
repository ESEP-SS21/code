#include <logic/stm/StmAnswerTransferReq/answer_transfer_req_states.h>

namespace logic {
namespace stm {
namespace StmAnswerTransferReq {

STATE_INIT(Waiting)
STATE_INIT(WaitingForSpace)

bool Waiting::wrpc_trns_rq(int payload) {
    if(_datamodel->_unit_type==datamodel::UnitType::SECONDARY){
        auto enc_wrpc = datamodel::EncodedWorkpiece(payload);
        auto wrpc = std::make_shared<datamodel::Workpiece>(enc_wrpc);
        _datamodel->set_pending_transfer(wrpc);

        if(_datamodel->_belt_blocked == false){
            _eventSender->send({ EventType::EVNT_ACK, 0, true });
            _eventSender->send({ EventType::EVNT_ACT_BELT_FWD, 0, true });
        }
        else{
            switch_state<WaitingForSpace>();
        }
    }
    return true;
}


bool WaitingForSpace::lb_he_blck() {
    _eventSender->send({ EventType::EVNT_ACK, 0, true });
    _eventSender->send({ EventType::EVNT_ACT_BELT_FWD, 0, true });
    switch_state<Waiting>();
    return true;
}

void WaitingForSpace::reset_to_start() {
    switch_state<Waiting>();
}

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
