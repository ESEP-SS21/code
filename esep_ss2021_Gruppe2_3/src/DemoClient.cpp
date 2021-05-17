#include "DemoClient.h"
#include <iostream>
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/Event.h"

DemoClient::DemoClient(const std::string& dispatcher_name, const std::string& name) :
        DispatcherClient(dispatcher_name, name) {
    subscribe( {
        dispatcher::EventType::EVNT_SEN_LB_HE_BLCK,
        dispatcher::EventType::EVNT_SEN_HEIGHT_HE,
        dispatcher::EventType::EVNT_CTRL_T_STR_PRS_SRT,
        dispatcher::EventType::EVNT_CTRL_T_STP_PRS_SRT,
        dispatcher::EventType::EVNT_CTRL_T_RST_PRS_SRT
    });
}

void DemoClient::handle(dispatcher::Event& event) {
    if (event.type == dispatcher::EventType::EVNT_SEN_LB_HE_BLCK) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_SEN_HEIGHT_REQ, 0, false };
        send(e, 20);
    }
    if (event.type == dispatcher::EventType::EVNT_SEN_HEIGHT_HE) {
        _logger->trace("Height = '{}'", event.payload);
    }
    if (event.type == dispatcher::EventType::EVNT_CTRL_T_STR_PRS_SRT) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_ACT_BELT_FWD, 0, false };
        send(e, 20);
    }
    if (event.type == dispatcher::EventType::EVNT_CTRL_T_STP_PRS_SRT) {
        dispatcher::Event e = { dispatcher::EventType::EVNT_ACT_BELT_STP, 0, false };
        send(e, 20);
    }
    if (event.type == dispatcher::EventType::EVNT_CTRL_T_RST_PRS_SRT) {
            dispatcher::Event e = { dispatcher::EventType::EVNT_ACT_BELT_BWD, 0, false };
            send(e, 20);
        }
}

DemoClient::~DemoClient() {

}
