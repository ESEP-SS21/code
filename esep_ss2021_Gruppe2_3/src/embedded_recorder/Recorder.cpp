#include <embedded_recorder/Recorder.h>
#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>
#include "utils.h"

namespace embedded_recorder {

Recorder::Recorder(const std::string& dispatcher_name) :
        DispatcherClient(dispatcher_name, "Recorder Manager") {

    subscribe(dispatcher::EventType::EVNT_SEN_ESTOP_ON);
    subscribe(dispatcher::EventType::EVNT_SEN_ESTOP_OFF);
    subscribe(dispatcher::EventType::EVNT_CTRL_T_STR_PRS_LNG);
    subscribe(dispatcher::EventType::EVNT_CTRL_T_STR_PRS_SRT);
    subscribe(dispatcher::EventType::EVNT_CTRL_T_STP_PRS_LNG);
    subscribe(dispatcher::EventType::EVNT_CTRL_T_STP_PRS_SRT);
    subscribe(dispatcher::EventType::EVNT_CTRL_T_STP_PRS_LNG);
    subscribe(dispatcher::EventType::EVNT_CTRL_T_STP_PRS_SRT);
    subscribe(dispatcher::EventType::EVNT_CTRL_T_RST_PRS_LNG);
    subscribe(dispatcher::EventType::EVNT_CTRL_T_RST_PRS_SRT);
    subscribe(dispatcher::EventType::EVNT_SEN_LB_ST_BLCK);
    subscribe(dispatcher::EventType::EVNT_SEN_LB_ST_CLR);
    subscribe(dispatcher::EventType::EVNT_SEN_LB_HE_BLCK);
    subscribe(dispatcher::EventType::EVNT_SEN_LB_HE_CLR);
    subscribe(dispatcher::EventType::EVNT_SEN_LB_SW_BLCK);
    subscribe(dispatcher::EventType::EVNT_SEN_LB_SW_CLR);
    subscribe(dispatcher::EventType::EVNT_SEN_LB_RA_BLCK);
    subscribe(dispatcher::EventType::EVNT_SEN_LB_RA_CLR);
    subscribe(dispatcher::EventType::EVNT_SEN_LB_EN_BLCK);
    subscribe(dispatcher::EventType::EVNT_SEN_LB_EN_CLR);
    subscribe(dispatcher::EventType::EVNT_SEN_METAL_DTC);
    subscribe(dispatcher::EventType::EVNT_SEN_HEIGHT_HE);

    _file_name = utils::system_start_time_and_date_string;
    _json = {};
}

void Recorder::handle(dispatcher::Event& event) {
    using nlohmann::json;
    const long ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - utils::start_time).count();
    json j_ev = event;
    json j_ms = { { "time", ms }, { "evnt", event } };
    _json.push_back(j_ms);
}

Recorder::~Recorder() {
    std::ofstream file("records/" + _file_name + ".json");
    file << _json.dump(2);
}

}