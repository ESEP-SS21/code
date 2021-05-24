#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>
#include "utils.h"
#include <recorder_replayer/Recorder.h>

namespace recorder_replayer {

Recorder::Recorder(const std::string& dispatcher_name) :
                DispatcherClient(dispatcher_name, "Recorder Manager") {
    subscribe_evnt(dispatcher::EventType::AnotherEvent);
    _file_name = utils::system_start_time_and_date_string;
    _json = {};
}

void Recorder::handle(dispatcher::Event& event){
    using nlohmann::json;
    const long ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - utils::start_time).count() ;
    json j_ev = event;
    json j_ms = {{"time", ms}, {"evnt", event}};
    _json.push_back(j_ms);
}

Recorder::~Recorder() {
    std::ofstream file("records/" + _file_name + ".json");
    file << _json.dump(2);
}

}
