#include <embedded_recorder/replayer.h>
#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include <fstream>
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>
#include "utils.h"

namespace embedded_recorder {

using nlohmann::json;

Replayer::Replayer(const std::string& dispatcher_name, const std::string& filename) :
        DispatcherClient(dispatcher_name, "Replay Manager"), _file_name(filename) {
    std::ifstream file("records/" + filename, std::ifstream::in);
    _json = json::parse(file);
    start();
}

void Replayer::replay(const std::string& input) {
    for (unsigned i = 0; i < _json.size(); i++) {
        auto curr_evnt_ms_from_start = std::chrono::milliseconds(_json[i]["time"]);
        auto next_event_time = utils::start_time + curr_evnt_ms_from_start;
        auto event = _json[i]["evnt"].get<dispatcher::Event>();

        const auto now = std::chrono::high_resolution_clock::now();
        if (now < next_event_time) {
            const auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(
                    next_event_time - now);
            std::this_thread::sleep_for(time_diff);
        }
        send(event);
    }
}

void Replayer::start() {
    _replay_thread = std::thread([this] {replay(_file_name);});
}

Replayer::~Replayer() {
    if (_replay_thread.joinable())
        _replay_thread.join();
}

}
