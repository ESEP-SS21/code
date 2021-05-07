#ifndef SRC_DEMOCLIENT_H_
#define SRC_DEMOCLIENT_H_
#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/Event.h"
#include "dispatcher/DispatcherClient.h"

class DemoClient: public dispatcher::DispatcherClient {
public:
    DemoClient(const std::string& disp_name, std::unique_ptr<dispatcher::cnnMngmnt::QnxChannel> channel);
    void handle(dispatcher::Event& event);
    virtual ~DemoClient();
};

#endif /* SRC_DEMOCLIENT_H_ */
