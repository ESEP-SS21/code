#include <logic/stm/StmAnswerTransferReq/answer_transfer_req_states.h>

namespace logic {
namespace stm {
namespace StmAnswerTransferReq {



using namespace dispatcher;

STATE_INIT(Waiting)

bool Waiting::handle(const Event &event) {
    switch (event.type) {
        case EventType::EVNT_WRPC_TRNS_RQ:
            if (_datamodel->_unit_type == datamodel::UnitType::SECONDARY) {
                auto enc_wrpc = datamodel::EncodedWorkpiece(event.payload);
                auto wrpc = std::make_shared<datamodel::Workpiece>(enc_wrpc);
                _datamodel->set_pending_transfer(wrpc);

                if (!_datamodel->_belt_blocked) {
                    _eventSender->send({EventType::EVNT_ACK, 0, true});
                    _eventSender->send({EventType::EVNT_ACT_BELT_FWD, 0, true});
                } else {
                    switch_state<WaitingForSpace>();
                }
            }
            return true;
        default:
            return false;
    }
}

STATE_INIT(WaitingForSpace)

bool WaitingForSpace::handle(const Event &event) {
    switch (event.type) {
        case dispatcher::EventType::EVNT_RST_TO_SRT:
            switch_state<Waiting>();
            return true;
        case EventType::EVNT_SEN_LB_HE_BLCK:
            _eventSender->send({EventType::EVNT_ACK, 0, true});
            _eventSender->send({EventType::EVNT_ACT_BELT_FWD, 0, true});
            switch_state<Waiting>();
            return true;
        default:
            return false;
    }
}

} /* namespace StmAnswerTransferReq */
} /* namespace stm */
} /* namespace logic */
