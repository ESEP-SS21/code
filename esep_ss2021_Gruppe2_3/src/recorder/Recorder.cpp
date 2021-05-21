#include <nlohmann/json.hpp>
#include <recorder/Recorder.h>
#include <thread>

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
    json j_ms = {{"TIME", ms}, {"EVNT", event}};
    j.push_back(j_ms);

    _file = std::ofstream("records/" + _date + ".json", std::ofstream::trunc);
    _file << j.dump(2);
    _file.close();
}

void replay(json j){
    using nlohmann::json;

    auto event = j.get<Event>();

    std::cout << "Hello" << std::endl;


}

} /* namespace */
