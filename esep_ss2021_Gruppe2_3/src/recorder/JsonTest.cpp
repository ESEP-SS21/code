#include <recorder/JsonTest.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

namespace recorder {

void JsonTest::test(){
    using nlohmann::json;
    using namespace dispatcher;

    const auto start_time = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::ofstream file("test.json");

    Event e(EventType::AnotherEvent, false, 12);
    json event_j = e;

    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() ;
    json j =
        {
            ms,
            event_j
        };

    file << j.dump(4);
}

} /* namespace Logger */
