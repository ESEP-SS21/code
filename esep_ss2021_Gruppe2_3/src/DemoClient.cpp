#include <DemoClient.h>
#include <iostream>
#include "utils/connManagement/QnxConnection.h"
#include "utils/connManagement/QnxChannel.h"

DemoClient::DemoClient(const std::string& disp_name, std::unique_ptr<connManagement::QnxChannel> channel) :
    DispatcherClient(disp_name, std::move(channel)) {
}

void DemoClient::handle(dispatcher::Event& event){
    std::cout<<"event_id:"<<event.number<<"payload: "<<event.payload<<std::endl;
}

DemoClient::~DemoClient() {
    // TODO Auto-generated destructor stub
}

