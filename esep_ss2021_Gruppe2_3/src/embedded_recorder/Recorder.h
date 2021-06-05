#pragma once

#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"
#include <fstream>

namespace embedded_recorder {

class Recorder: public dispatcher::DispatcherClient {
public:
    Recorder(const std::string& dispatcher_name, const std::string& filename);
    void handle(dispatcher::Event& event);
    virtual ~Recorder();
private:
    std::string _path;
    nlohmann::json _json;
};

}

