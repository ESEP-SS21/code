#include <DemoClient.h>
#include <iostream>
#include "dispatcher/connManagement/QnxConnection.h"
#include "dispatcher/connManagement/QnxChannel.h"

DemoClient::DemoClient(const std::string& disp_name, std::unique_ptr<dispatcher::cnnMngmnt::QnxChannel> channel) :
    DispatcherClient(disp_name, std::move(channel)) {
}

void DemoClient::handle(dispatcher::Event& event){
    std::cout<<"event_id:"<<event.number<<"payload: "<<event.payload<<std::endl;
}

DemoClient::~DemoClient() {
    // TODO Auto-generated destructor stub
}

