#pragma once

#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"
#include <fstream>
#include "event_json_converter.h"

namespace embedded_recorder {

using namespace dispatcher;

class Recorder: public DispatcherClient {
public:
    Recorder(const std::string& dispatcher_name, const std::string& filename);
    void handle(Event& event);
    virtual ~Recorder();
private:
    std::string _path;
    nlohmann::json _json;
};

}

