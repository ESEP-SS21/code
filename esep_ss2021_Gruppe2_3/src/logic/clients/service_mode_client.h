#pragma once
#include "../stm/service_mode/service_mode_context.h"
#include "dispatcher/DispatcherClient.h"

namespace logic {
namespace clients {

using namespace logic::stm::stm_service_mode;

class ServiceModeClient : public dispatcher::DispatcherClient{
public:
    ServiceModeClient(const std::string& dispatcher_name, datamodel::UnitData * data)
    :DispatcherClient(dispatcher_name, "ServiceModeClientClient"), _context(this, data) {
        subscribe( {
            EventType::EVNT_SEN_LB_ST_CLR,
            EventType::EVNT_SEN_LB_EN_CLR,
            EventType::EVNT_SEN_LB_SW_CLR,
            EventType::EVNT_SEN_LB_RA_CLR,
            EventType::EVNT_SEN_METAL_DTC,
            EventType::EVNT_SRV_STR,
            EventType::EVNT_SEN_HEIGHT_HE,
            EventType::EVNT_CTRL_T_RST_PRS_SRT,
            EventType::EVNT_TIM_ALRT,
            EventType::EVNT_CTRL_T_STP_PRS_LNG
        });
    }
    virtual ~ServiceModeClient() = default;
protected:
    void handle(dispatcher::Event& event) {
        _context.handle(event);
    }
    ServiceModeContext _context;
};

}
}
