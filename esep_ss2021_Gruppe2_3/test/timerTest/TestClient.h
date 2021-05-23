#pragma once

#include "../src/dispatcher/dispatcher.h"
#include "../src/timer/ASyncTimerService.h"
#include "../src/dispatcher/cnnMngmnt/QnxChannel.h"
#include "../src/dispatcher/cnnMngmnt/QnxConnection.h"
#include "../src/dispatcher/Event.h"
#include "../src/dispatcher/SyncMsg.h"

namespace test{
namespace timerTest{


class TestClient {
public:
    TestClient(const std::string& dispatcher_name, const std::string& name);
    virtual ~TestClient();

    void send(dispatcher::Event event, int prio) const;
    void subscribe(dispatcher::EventType event_type);
    void subscribe(std::initializer_list<dispatcher::EventType> event_types);
    dispatcher::Event recieve_event();

private:
    std::string _name;
    std::string _dispatcher_name;
    std::unique_ptr<dispatcher::cnnMngmnt::QnxChannel> _channel;
    std::unique_ptr<dispatcher::cnnMngmnt::QnxConnection> _dispatcher_connection;
};

} /*namespace*/
} /*namespace*/
