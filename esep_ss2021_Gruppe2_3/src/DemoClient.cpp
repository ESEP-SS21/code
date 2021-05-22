#include "DemoClient.h"
#include <iostream>
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/Event.h"

DemoClient::DemoClient(const std::string& dispatcher_name, const std::string& name) :
        DispatcherClient(dispatcher_name, name) {
    subscribe({
        dispatcher::EventType::EVNT_CTRL_T_STR_PRS_SRT,
        dispatcher::EventType::EVNT_TIM_ALRT
    });
}

void DemoClient::handle(dispatcher::Event& event) {
    if(event.type == dispatcher::EventType::EVNT_CTRL_T_STR_PRS_SRT){
        send(dispatcher::Event::CreateTimer(10, 1000, false),20);
    }
    if(event.type == dispatcher::EventType::EVNT_TIM_ALRT && event.payload==10){
        _logger->debug("timer elapsed");
    }
}

DemoClient::~DemoClient() {

}
