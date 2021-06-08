#include <logic/clients/operation_manager_client.h>
#include "dispatcher/Event.h"

namespace logic {
namespace clients {

OperationManagerClient::OperationManagerClient(const std::string& dispatcher_name, datamodel::UnitData *data) :
        DispatcherClient(dispatcher_name, "OperationManagerClient"), _context(this, data) {
    subscribe( {
        EventType::EVNT_CTRL_T_STR_PRS_SRT,
        EventType::EVNT_CTRL_T_STR_PRS_LNG,
        EventType::EVNT_CTRL_T_STP_PRS_SRT,
        EventType::EVNT_CTRL_T_RST_PRS_SRT,
        EventType::EVNT_SEN_ESTOP_ON,
        EventType::EVNT_SEN_ESTOP_OFF,
        EventType::EVNT_CONN_LOST,
        EventType::EVNT_ERR,
        EventType::EVNT_ERR_GONE,
        EventType::EVNT_WRN,
        EventType::EVNT_WRN_GONE,
        EventType::EVNT_SRV_DONE,
    });
}

OperationManagerClient::~OperationManagerClient() {

}

}
}
