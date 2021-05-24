#pragma once

#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"

namespace recorder_replayer {

class Replayer: public dispatcher::DispatcherClient {
public:
    Replayer(const std::string& dispatcher_name, const std::string& input);
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

