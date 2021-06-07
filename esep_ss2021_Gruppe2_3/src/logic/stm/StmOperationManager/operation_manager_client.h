#pragma once
#include "operation_manager_context.h"
#include "dispatcher/DispatcherClient.h"

namespace logic {
namespace stm {
namespace operationManagerStm {

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

} /* namespace recieveWrpcStm */
} /* namespace stm */
} /* namespace logic */

