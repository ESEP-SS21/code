#pragma once
#include "logic/stm/StmSortWrpc/sort_wrpc_context.h"
#include "dispatcher/DispatcherClient.h"

namespace clients {

using namespace logic::stm::sortWrpcStm;

class SortWrpcClient : public dispatcher::DispatcherClient{
public:
    SortWrpcClient(const std::string& dispatcher_name, datamodel::UnitData * data)
    :DispatcherClient(dispatcher_name, "SortWrpcClient"), _context(this, data) {
        subscribe( {
            EventType::EVNT_HIST,
            EventType::EVNT_RST_TO_SRT,
            EventType::EVNT_SEN_LB_SW_BLCK,
            EventType::EVNT_SEN_LB_SW_CLR,
            EventType::EVNT_SEN_LB_RA_CLR,
            EventType::EVNT_TIM_ALRT,
        });
    }
    virtual ~SortWrpcClient() = default;
protected:
    void handle(dispatcher::Event& event) {
        _context.handle(event);
    }
    SortWrpcContext _context;
};

}
