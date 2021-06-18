#include <embedded_recorder/recorder.h>
#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>
#include "utils.h"

namespace embedded_recorder {
using namespace dispatcher;

Recorder::Recorder(const std::string &dispatcher_name, const std::string &filename) :
    DispatcherClient(dispatcher_name, "Recorder Manager") {
    subscribe({
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
        //EventType::EVNT_SEN_LB_ST_CLR,
        EventType::EVNT_SEN_LB_HE_BLCK,
        //EventType::EVNT_SEN_LB_HE_CLR,
        EventType::EVNT_SEN_LB_SW_BLCK,
        EventType::EVNT_SEN_LB_SW_CLR,
        //EventType::EVNT_SEN_LB_RA_BLCK,
        EventType::EVNT_SEN_LB_RA_CLR,
        EventType::EVNT_SEN_LB_EN_BLCK,
        EventType::EVNT_SEN_LB_EN_CLR,
        EventType::EVNT_SEN_METAL_DTC,
        EventType::EVNT_SEN_HEIGHT_HE
    });

    std::string file_name = filename == "" ? utils::system_start_time_and_date_string : filename;
    _path = "records/" + file_name + ".json";
    _logger->info("Recorder will save to '{}'", _path);
    _json = {};
}

void Recorder::handle(dispatcher::Event &event) {
    using nlohmann::json;
    const long ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - utils::start_time).count();
    json j_ev = event;
    json j_ms = {{"time", ms},
                 {"evnt", event}};
    _json.push_back(j_ms);
}

Recorder::~Recorder() {
    _logger->info("Saving to '{}'", _path);
    std::ofstream file(_path);
    file << _json.dump(2);
}

}
