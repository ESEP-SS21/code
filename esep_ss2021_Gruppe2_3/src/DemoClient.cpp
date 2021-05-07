#include <DemoClient.h>
#include <iostream>
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/cnnMngmnt/QnxChannel.h"

DemoClient::DemoClient(const std::string& name) :
        DispatcherClient(name) {
}

void DemoClient::handle(dispatcher::Event& event) {
    std::cout << "event_id:" << event.number << "payload: " << event.payload << std::endl;
}

DemoClient::~DemoClient() {
    // TODO Auto-generated destructor stub
}
