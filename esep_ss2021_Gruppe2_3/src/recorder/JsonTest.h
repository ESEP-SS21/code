#pragma once
#include <fstream>
#include "dispatcher/Event.h"


namespace recorder {

class JsonTest {
public:
    virtual ~JsonTest() = default;
    void test();
};

} /* namespace Logger */
