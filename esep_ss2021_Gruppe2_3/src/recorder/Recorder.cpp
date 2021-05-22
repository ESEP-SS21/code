#include <nlohmann/json.hpp>
#include <recorder/Recorder.h>
#include <thread>
#include <ctime>

#include "utils.h"


namespace recorder {


Recorder::Recorder(){
    _date = utils::current_time_and_date;
    _file = std::ofstream("records/" + _date + ".json");
    _file << "[]\n";
    _file.close();
}

void Recorder::record(Event event){
    using nlohmann::json;
    std::ifstream json_file("records/" + _date + ".json");
    std::cout << _date << std::endl;
    json j = json::parse(json_file);
    const long ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - utils::start_time).count() ;
    json j_ev = event;
    json j_ms = {{"time", ms}, {"evnt", event}};
    j.push_back(j_ms);

    _file = std::ofstream("records/" + _date + ".json", std::ofstream::trunc);
    _file << j.dump(2);
    _file.close();
}

void Recorder::replay(const std::string& input){
    using nlohmann::json;

    std::ifstream json_file(input);
    json j = json::parse(json_file);

    int prev_ms = 0;
    for(unsigned i = 0; i < j.size(); i++){
        int ms = j[i]["time"];
        auto event = j[i]["evnt"].get<Event>();
        std::this_thread::sleep_for(std::chrono::milliseconds(ms-prev_ms));
        ms = prev_ms;
        //TODO: Dispatch Event

    }
}

} /* namespace */
