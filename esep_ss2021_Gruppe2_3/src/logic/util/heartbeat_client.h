#pragma once
#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"

namespace logic {
namespace util {

class HeartbeatClient : public dispatcher::DispatcherClient {
public:
    HeartbeatClient(const std::string& dispatcher_name);
    virtual ~HeartbeatClient() = default;

private:
    void handle(dispatcher::Event& event) override;
    Logger::Logger _logger { Logger::get() };
};

}
}

