#include <embedded_recorder/Replayer.h>
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

Replayer::Replayer(const std::string& dispatcher_name, const std::string& input) :
        DispatcherClient(dispatcher_name, "Replay Manager"), _file_name(input) {
    std::ifstream file(input, std::ifstream::in);
    _json = json::parse(file);
}

void Replayer::replay(const std::string& input) {
    long prev_ms = 0;
    for (unsigned i = 0; i < _json.size(); i++) {
        const long curr_evnt_ms = _json[i]["time"];
        const auto event = _json[i]["evnt"].get<dispatcher::Event>();
        std::this_thread::sleep_for(std::chrono::milliseconds(curr_evnt_ms - prev_ms));
        send_evnt(event);
        prev_ms = curr_evnt_ms;
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
