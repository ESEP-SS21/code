#pragma once
#include "logic/stm/StmRecieveWrpc/recieve_wrpc_context.h"
#include "dispatcher/DispatcherClient.h"

namespace clients {

using namespace logic::stm::receiveWrpcStm;

class ReceiveWrpcClient : public dispatcher::DispatcherClient{
public:
    ReceiveWrpcClient(const std::string& dispatcher_name, datamodel::UnitData * data)
    :DispatcherClient(dispatcher_name, "ReceiveWrpcClient"), _context(this, data) {
        subscribe( {
            EventType::EVNT_HIST,
            EventType::EVNT_RST_TO_SRT,
            EventType::EVNT_ACT_BELT_FWD,
            EventType::EVNT_SEN_LB_ST_BLCK,
            EventType::EVNT_ACT_BELT_STP,
        });
    }
    virtual ~ReceiveWrpcClient() = default;
protected:
    void handle(dispatcher::Event& event) {
        _context.handle(event);
    }
    ReceiveWrpcContext _context;
};

}
