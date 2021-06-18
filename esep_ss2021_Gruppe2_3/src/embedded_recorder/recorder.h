#pragma once

#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"
#include <fstream>
#include "../dispatcher/connection_management/QnxChannel.h"
#include "../dispatcher/connection_management/QnxConnection.h"
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

