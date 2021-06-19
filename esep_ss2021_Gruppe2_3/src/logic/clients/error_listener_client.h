#pragma once
#include "../stm/StmErrorListener/error_listener_context.h"
#include "dispatcher/DispatcherClient.h"

namespace logic {
namespace clients {

using namespace logic::stm::StmErrorListener;

class ErrorListenerClient : public dispatcher::DispatcherClient{
public:
    ErrorListenerClient(const std::string& dispatcher_name, datamodel::UnitData * data)
    :DispatcherClient(dispatcher_name, "ErrorListenerClient"), _context(this, data) {
        subscribe( {
            EventType::EVNT_ERR,
            EventType::EVNT_SEN_LB_RA_CLR,
            EventType::EVNT_SEN_ESTOP_ON,
            EventType::EVNT_CONN_LOST
        });
    }
    virtual ~ErrorListenerClient() = default;
protected:
    void handle(dispatcher::Event& event) {
        _context.handle(event);
    }
    ErrorListenerContext _context;
};

}
}
