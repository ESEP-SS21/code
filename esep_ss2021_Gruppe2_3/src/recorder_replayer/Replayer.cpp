#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include <fstream>
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>
#include "utils.h"
#include <recorder_replayer/Replayer.h>

namespace recorder_replayer {
using nlohmann::json;

Replayer::Replayer(const std::string& dispatcher_name, const std::string& input) :
        DispatcherClient(dispatcher_name, "Replay Manager") {
    _replay_thread = std::thread([this, input] {this->replay(input);});

    std::ifstream file(input, std::ifstream::in);
    _json = json::parse(file);
}
void Replayer::replay(const std::string& input) {
    int prev_ms = 0;
    for (unsigned i = 0; i < _json.size(); i++) {
        int ms = _json[i]["time"];
        auto event = _json[i]["evnt"].get<dispatcher::Event>();
        std::this_thread::sleep_for(std::chrono::milliseconds(ms - prev_ms));
        ms = prev_ms;
        send_evnt(event, 20);
    }
}

void Replayer::handle(dispatcher::Event& event) {
}

Replayer::~Replayer() {
    _replay_thread.join();
}

}
