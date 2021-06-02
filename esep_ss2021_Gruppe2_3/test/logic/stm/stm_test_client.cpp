#include "stm_test_client.h"

using namespace dispatcher;

StmTestClient::StmTestClient() {
}

void StmTestClient::send(Event event, int prio){
    _event_queue.push(event);
}

Event StmTestClient::get_last_event() {
    Event e = _event_queue.front();
    _event_queue.pop();
    return e;
}

