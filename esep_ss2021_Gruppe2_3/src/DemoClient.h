#pragma once

#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/DispatcherClient.h"

class DemoClient: public dispatcher::DispatcherClient {
public:
    DemoClient(const std::string& dispatcher_name, const std::string& name);
    virtual ~DemoClient();

private:
    void handle(dispatcher::Event& event) override;
    Logger::Logger _logger { Logger::get() };
};
