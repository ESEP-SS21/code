#pragma once
#include <fstream>
#include "dispatcher/Event.h"
#include <chrono>


namespace recorder {
using namespace dispatcher;

class Recorder {
public:
    virtual ~Recorder() = default;
    void record(Event e);
private:
   const static std::chrono::system_clock::time_point start_time;
    std::ofstream _file{"test.json"};
};

} /* namespace */
