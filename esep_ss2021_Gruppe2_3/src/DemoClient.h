#pragma once

#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/DispatcherClient.h"

class DemoClient: public dispatcher::DispatcherClient {
public:
    DemoClient(const std::string& name);
    virtual ~DemoClient();

    void handle(dispatcher::Event& event);
private:
    Logger::Logger _logger { Logger::get() };
};
