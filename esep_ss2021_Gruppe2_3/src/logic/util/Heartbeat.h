#pragma once
#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"

namespace logic {
namespace util {

class Heartbeat : public dispatcher::DispatcherClient {
public:
    Heartbeat(const std::string& dispatcher_name);
    virtual ~Heartbeat() = default;

private:
    void handle(dispatcher::Event& event) override;
    Logger::Logger _logger { Logger::get() };
};

}
}

