#include <nlohmann/json.hpp>
#include <recorder/Recorder.h>
#include <thread>

namespace recorder {

const std::chrono::system_clock::time_point Recorder::start_time {std::chrono::system_clock::now()};

void Recorder::record(Event event){
    using nlohmann::json;
    const long ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start_time).count() ;
    json j =
        {
            ms,
            event
        };

    _file << j.dump(2);
}

} /* namespace */
