#pragma once
#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"

namespace logic {

class Heartbeat : public dispatcher::DispatcherClient {
public:
    Heartbeat(const std::string& dispatcher_name, uint16_t timer_id);
    virtual ~Heartbeat();

private:
    uint16_t _timer_id;
    void handle(dispatcher::Event& event) override;
    Logger::Logger _logger { Logger::get() };
};

} /* namespace logic */

