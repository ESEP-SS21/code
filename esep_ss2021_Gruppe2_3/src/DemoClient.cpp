#include <DemoClient.h>
#include <iostream>
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/Event.h"

DemoClient::DemoClient(const std::string& name) :
        DispatcherClient(name) {
}

void DemoClient::handle(dispatcher::Event& event) {
    std::cout << "Demo Client recieved Event:" << std::endl << "Type:" << event.type << std::endl << "payload: " << event.payload << std::endl << std::endl;
}

DemoClient::~DemoClient() {
    // TODO Auto-generated destructor stub
}
