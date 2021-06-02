#include <logic/util/Heartbeat.h>

namespace logic {
namespace util {

using namespace dispatcher;

Heartbeat::Heartbeat(const std::string& dispatcher_name) : DispatcherClient(dispatcher_name, "Heartbeat") {
    subscribe(EventType::EVNT_TIM_ALRT);
    Event timer_request = Event::CreateTimer(TimerID::HEARTBEAT, 100, false);
    send(timer_request,20);
}

void Heartbeat::handle(dispatcher::Event& event) {
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
