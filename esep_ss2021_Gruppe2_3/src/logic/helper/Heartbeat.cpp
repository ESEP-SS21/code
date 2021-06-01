#include <logic/helper/Heartbeat.h>

namespace logic {

using namespace dispatcher;

Heartbeat::Heartbeat(const std::string& dispatcher_name, uint16_t timer_id) : DispatcherClient(dispatcher_name, "Heartbeat") {
    _timer_id = timer_id;
    subscribe(EventType::EVNT_TIM_ALRT);
    Event timer_request = Event::CreateTimer(_timer_id, 100, true);
    send(timer_request,20);
}

void Heartbeat::handle(dispatcher::Event& event) {
    if(event.type == EventType::EVNT_TIM_ALRT){
        if(event.payload == _timer_id){
            Event timer_request = Event::CreateTimer(_timer_id, 100, true);
            send(timer_request,20);
        }
    }
}

Heartbeat::~Heartbeat() {

}

} /* namespace logic */
