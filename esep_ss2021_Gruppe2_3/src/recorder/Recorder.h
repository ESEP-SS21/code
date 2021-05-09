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

private:
    std::ofstream _file;
};

} /* namespace */
