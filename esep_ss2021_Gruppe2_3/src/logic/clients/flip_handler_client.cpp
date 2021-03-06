#include <logic/clients/flip_handler_client.h>

namespace logic {
namespace clients {

using namespace dispatcher;

FlipHandlerClient::FlipHandlerClient(const std::string& dispatcher_name, logic::datamodel::UnitData *data):
        DispatcherClient(dispatcher_name, "FlipHandler"){
    _data = data;
    subscribe(EventType::EVNT_WRPC_FLP);
}

void FlipHandlerClient::handle(dispatcher::Event& event) {
    if(event.type == EventType::EVNT_WRPC_FLP && _data->_unit_type==datamodel::UnitType::PRIMARY){
        datamodel::EncodedWorkpiece flipped_wrpc(event.payload);
        _data->wrpc_order_reset(flipped_wrpc.get_type());
    }
}

}
}
