
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

Replayer::Replayer(const std::string& dispatcher_name, const std::string& input) :
        DispatcherClient(dispatcher_name, "Replay Manager") {
        _replay_thread = std::thread([this, input] {this->replay(input);});

}
void Replayer::replay(const std::string& input){

    using nlohmann::json;
    std::ifstream json_file(input, std::ifstream::in);
    json json_input = json::parse(json_file);

    int prev_ms = 0;
    for(unsigned i = 0; i < json_input.size(); i++){
        int ms = json_input[i]["time"];
        auto event = json_input[i]["evnt"].get<dispatcher::Event>();
        std::this_thread::sleep_for(std::chrono::milliseconds(ms-prev_ms));
        ms = prev_ms;
        send_evnt(event,20);
    }
    json_file.close();

}

void Replayer::handle(dispatcher::Event& event){
}


Replayer::~Replayer() {
    _replay_thread.join();
}

}
