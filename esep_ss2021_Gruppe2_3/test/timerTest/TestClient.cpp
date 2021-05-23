#include <timerTest/TestClient.h>

using namespace dispatcher;
namespace test {
namespace timerTest {

TestClient::TestClient(const std::string& dispatcher_name, const std::string& name) :
        DispatcherClient(dispatcher_name, name) {
}

Event TestClient::recieve_event() {
    std::unique_lock<std::mutex> lg(_queue_mutex);
    _queue_cond_var.wait(lg, [&] {return !_event_queue.empty();});
    Event e = _event_queue.front();
    _event_queue.pop();
    return e;
}

void TestClient::handle(Event& event) {
    std::lock_guard<std::mutex> lg(_queue_mutex);
    _event_queue.push(event);
    _queue_cond_var.notify_one();
}

} /*namespace*/
} /*namespace*/
