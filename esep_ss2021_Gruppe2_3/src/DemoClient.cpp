/*
 * DemoClient.cpp
 *
 *  Created on: 07.05.2021
 *      Author: jendr
 */

#include <DemoClient.h>
#include <iostream>

DemoClient::DemoClient(const std::string& disp_name, std::unique_ptr<connManagement::IIpcChannel> channel) :
    DispatcherClient(disp_name, std::move(channel)) {
}

void DemoClient::handle(dispatcher::Event& event){
    std::cout<<"event_id:"<<event.number<<"payload: "<<event.payload<<std::endl;
}

DemoClient::~DemoClient() {
    // TODO Auto-generated destructor stub
}

