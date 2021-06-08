#include <logic/clients/heartbeat_client.h>

namespace logic {
namespace clients {

using namespace dispatcher;

HeartbeatClient::HeartbeatClient(const std::string& dispatcher_name) : DispatcherClient(dispatcher_name, "Heartbeat") {
    subscribe(EventType::EVNT_TIM_ALRT);
    Event timer_request = Event::CreateTimer(TimerID::HEARTBEAT, 100, false);
    send(timer_request,20);
}

void HeartbeatClient::handle(dispatcher::Event& event) {
    if(event.type == EventType::EVNT_TIM_ALRT){
        if(TimerID(event.payload) == TimerID::HEARTBEAT){
            Event timer_request = Event::CreateTimer(TimerID::HEARTBEAT, 100, false);
            send(timer_request,20);
            Event heartbeat = { EventType::EVNT_HRTB, 0, true};
            send(heartbeat,20);
        }
    }
}

}
}
