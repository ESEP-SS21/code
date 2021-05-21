#include "DemoClient.h"
#include <iostream>
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/Event.h"

DemoClient::DemoClient(const std::string& dispatcher_name, const std::string& name) :
        DispatcherClient(dispatcher_name, name) {
}

void DemoClient::handle(dispatcher::Event& event) {

}

DemoClient::~DemoClient() {

}
