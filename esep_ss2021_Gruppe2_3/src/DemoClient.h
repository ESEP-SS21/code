/*
 * DemoClient.h
 *
 *  Created on: 07.05.2021
 *      Author: jendr
 */

#ifndef SRC_DEMOCLIENT_H_
#define SRC_DEMOCLIENT_H_
#include "dispatcher/Event.h"
#include "dispatcher/DispatcherClient.h"
#include "utils/connManagement/QnxChannel.h"

class DemoClient: public dispatcher::DispatcherClient {
public:
    DemoClient(const std::string& disp_name, std::unique_ptr<connManagement::IIpcChannel> channel);
    void handle(dispatcher::Event& event);
    virtual ~DemoClient();
};

#endif /* SRC_DEMOCLIENT_H_ */
