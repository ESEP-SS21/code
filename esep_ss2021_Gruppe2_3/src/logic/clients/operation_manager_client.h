#pragma once
#include "../stm/StmOperationManager/operation_manager_context.h"
#include "dispatcher/DispatcherClient.h"

namespace logic {
namespace clients {

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
}


