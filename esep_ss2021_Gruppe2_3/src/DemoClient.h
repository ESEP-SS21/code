#pragma once

#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/Event.h"
#include "dispatcher/DispatcherClient.h"

class DemoClient: public dispatcher::DispatcherClient {
public:
    DemoClient(const std::string& name);
    void handle(dispatcher::Event& event);
    virtual ~DemoClient();
};
