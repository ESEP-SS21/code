#pragma once
#include <fstream>
#include "dispatcher/Event.h"
#include <chrono>

namespace recorder {
using namespace dispatcher;

class Recorder {
public:
    Recorder();
    virtual ~Recorder() = default;
    void record(Event e);
    void replay(json j);

private:
    std::ofstream _file;
    std::string _date;
};

} /* namespace */
