#pragma once

#include "../src/dispatcher/dispatcherClient.h"
#include <queue>
#include <condition_variable>

namespace test {
namespace timerTest {

class TestClient: public dispatcher::DispatcherClient {
public:
    TestClient(const std::string& dispatcher_name, const std::string& name);
    void handle(dispatcher::Event& event);
    dispatcher::Event recieve_event();
private:
    std::queue<dispatcher::Event> _event_queue;
    std::mutex _queue_mutex;
    std::condition_variable _queue_cond_var;
};

} /*namespace*/
} /*namespace*/
