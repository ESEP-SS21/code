/*
 * RecorderManager.cpp
 *
 *  Created on: 24.05.2021
 *      Author: Lasse
 */

#include <recorder/RecorderManager.h>

namespace recorder {

RecorderManager::RecorderManager(const std::string& dispatcher_name, const std::string& input) :
        DispatcherClient(dispatcher_name, "Recorder Manager") {
        _replay_thread = std::thread([this, input] {this->playback_fnct(input);});
        subscribe_evnt(dispatcher::EventType::AnotherEvent);

        _date = utils::current_time_and_date;
        _file = std::ofstream("records/" + _date + ".json");
        _j = {};

}

void RecorderManager::playback_fnct(const std::string& input){

        using nlohmann::json;
        std::ifstream json_file(input, std::ifstream::in);
        json j = json::parse(json_file);

        int prev_ms = 0;
        for(unsigned i = 0; i < j.size(); i++){
            int ms = j[i]["time"];
            auto event = j[i]["evnt"].get<dispatcher::Event>();
            std::this_thread::sleep_for(std::chrono::milliseconds(ms-prev_ms));
            ms = prev_ms;
            send_evnt(event,20);
        }
        json_file.close();
}

void RecorderManager::handle(dispatcher::Event& event){
//    using nlohmann::json;
//    const long ms = std::chrono::duration_cast<std::chrono::milliseconds>(
//            std::chrono::system_clock::now() - utils::start_time).count() ;
//    json j_ev = event;
//    json j_ms = {{"time", ms}, {"evnt", event}};
//    _j.push_back(j_ms);

}


RecorderManager::~RecorderManager() {

    _file << _j.dump(2);
    _file.close();
    _replay_thread.join();

}

} /* namespace replayer */
