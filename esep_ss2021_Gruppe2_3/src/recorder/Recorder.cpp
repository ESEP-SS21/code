#include <nlohmann/json.hpp>
#include <recorder/Recorder.h>
#include <thread>

#include "utils.h"


namespace recorder {


Recorder::Recorder(){
    _file = std::ofstream("records/" + utils::current_time_and_date + ".json");
}

void Recorder::record(Event event){
    using nlohmann::json;
    const long ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - utils::start_time).count() ;
    json j =
        {
            ms,
            event
        };

    _file << j.dump(2);
}

} /* namespace */
