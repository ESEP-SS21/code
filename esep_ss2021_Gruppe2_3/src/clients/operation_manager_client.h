#pragma once
#include "logic/stm/StmOperationManager/operation_manager_context.h"
#include "dispatcher/DispatcherClient.h"

namespace clients {

using namespace logic;
using namespace logic::stm::operationManagerStm;

class OperationManagerClient : public dispatcher::DispatcherClient{
public:
    OperationManagerClient(const std::string& dispatcher_name, datamodel::UnitData * data);
    virtual ~OperationManagerClient();
protected:
    void handle(dispatcher::Event& event) {
        _context.handle(event);
    }
    OperationManagerContext _context;
};

}
