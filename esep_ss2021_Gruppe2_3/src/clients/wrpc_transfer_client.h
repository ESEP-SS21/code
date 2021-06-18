#pragma once
#include "logic/stm/StmWpTransfer/wp_transfer_context.h"
#include "dispatcher/DispatcherClient.h"

namespace clients {

using namespace logic::stm::StmWpTransfer;

class WrpcTransferClient : public dispatcher::DispatcherClient{
public:
    WrpcTransferClient(const std::string& dispatcher_name, datamodel::UnitData * data)
    :DispatcherClient(dispatcher_name, "WrpcTransferClient"), _context(this, data) {
        subscribe( {
            EventType::EVNT_HIST,
            EventType::EVNT_RST_TO_SRT,
            EventType::EVNT_TIM_ALRT,
            EventType::EVNT_SEN_LB_EN_BLCK,
            EventType::EVNT_SEN_LB_EN_CLR,
            EventType::EVNT_ACK,
        });
    }
    virtual ~WrpcTransferClient() = default;
protected:
    void handle(dispatcher::Event& event) {
        _context.handle(event);
    }
    WpTransferContext _context;
};

}
