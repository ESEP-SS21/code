#include <DemoClient.h>
#include <iostream>
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/Event.h"

DemoClient::DemoClient(const std::string& name) :
        DispatcherClient(name) {
}

void DemoClient::handle(dispatcher::Event& event) {

    _logger->info("Demo Client recieved Event {} payload {}",event.type, event.payload);
}

DemoClient::~DemoClient() {
    // TODO Auto-generated destructor stub
}
