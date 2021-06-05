#pragma once

#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"
#include <fstream>

namespace embedded_recorder {

class Recorder: public dispatcher::DispatcherClient {
public:
    Recorder(const std::string& dispatcher_name, const std::string& filename);
    void handle(dispatcher::Event& event);
    virtual ~Recorder();
private:
    std::string _path;
    nlohmann::json _json;

    using namespace dispatcher;
    const static std::initializer_list<dispatcher::EventType> _event_types = {
        EventType::EVNT_SEN_ESTOP_ON,
        EventType::EVNT_SEN_ESTOP_OFF,
        EventType::EVNT_CTRL_T_STR_PRS_LNG,
        EventType::EVNT_CTRL_T_STR_PRS_SRT,
        EventType::EVNT_CTRL_T_STP_PRS_LNG,
        EventType::EVNT_CTRL_T_STP_PRS_SRT,
        EventType::EVNT_CTRL_T_STP_PRS_LNG,
        EventType::EVNT_CTRL_T_STP_PRS_SRT,
        EventType::EVNT_CTRL_T_RST_PRS_LNG,
        EventType::EVNT_CTRL_T_RST_PRS_SRT,
        EventType::EVNT_SEN_LB_ST_BLCK,
        EventType::EVNT_SEN_LB_ST_CLR,
        EventType::EVNT_SEN_LB_HE_BLCK,
        EventType::EVNT_SEN_LB_HE_CLR,
        EventType::EVNT_SEN_LB_SW_BLCK,
        EventType::EVNT_SEN_LB_SW_CLR,
        EventType::EVNT_SEN_LB_RA_BLCK,
        EventType::EVNT_SEN_LB_RA_CLR,
        EventType::EVNT_SEN_LB_EN_BLCK,
        EventType::EVNT_SEN_LB_EN_CLR,
        EventType::EVNT_SEN_METAL_DTC,
        EventType::EVNT_SEN_HEIGHT_HE
    };
};

}

