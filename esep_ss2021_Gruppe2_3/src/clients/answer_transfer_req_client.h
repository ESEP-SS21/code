#pragma once
#include "logic/stm/StmAnswerTransferReq/answer_transfer_req_context.h"
#include "dispatcher/DispatcherClient.h"

namespace clients {

using namespace logic::stm::StmAnswerTransferReq;
using namespace logic;

class AnswerTransferReqClient : public dispatcher::DispatcherClient{
public:
    AnswerTransferReqClient(const std::string& dispatcher_name, datamodel::UnitData * data)
    :DispatcherClient(dispatcher_name, "AnswerTransferReqClient"), _context(this, data) {
        subscribe( {
            EventType::EVNT_HIST,
            EventType::EVNT_RST_TO_SRT,
            EventType::EVNT_WRPC_TRNS_RQ,
            EventType::EVNT_SEN_LB_HE_BLCK,
        });
    }
    virtual ~AnswerTransferReqClient() = default;
protected:
    void handle(dispatcher::Event& event) {
        _context.handle(event);
    }
    AnswerTransferReqContext _context;
};

}
