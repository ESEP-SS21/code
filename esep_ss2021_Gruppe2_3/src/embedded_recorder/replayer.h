#pragma once

#include "dispatcher/connection_management/QnxChannel.h"
#include "dispatcher/connection_management/QnxConnection.h"
#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"
#include "event_json_converter.h"

namespace embedded_recorder {

class Replayer: public dispatcher::DispatcherClient {
public:
    Replayer(const std::string& dispatcher_name, const std::string& filename);
    void handle(dispatcher::Event& event){};
    void start();
    virtual ~Replayer();
private:
    std::thread _replay_thread;
    void replay(const std::string& input);
    nlohmann::json _json;
    std::string _file_name;
};

}

