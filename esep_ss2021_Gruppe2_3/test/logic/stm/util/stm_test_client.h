#pragma once

#include "dispatcher/IEventSender.h"
#include <queue>
#include <condition_variable>

namespace test {
namespace logic {
namespace stm {

using namespace dispatcher;

class StmTestClient : public IEventSender {
public:
    StmTestClient();

    void send(Event event, int prio) override;

    Event get_last_event();

    bool empty();

private:
    std::queue<dispatcher::Event> _event_queue;

};

}
}
}
