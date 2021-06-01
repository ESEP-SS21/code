#include <logic/helper/FlipHandler.h>

namespace logic {
using namespace dispatcher;

FlipHandler::FlipHandler(const std::string& dispatcher_name, std::shared_ptr<logic::datamodel::UnitData> data):
        DispatcherClient(dispatcher_name, "FlipHandler"){
    _data = data;
    subscribe(EventType::EVNT_WRPC_FLP);
}

void FlipHandler::handle(dispatcher::Event& event) {
    if(event.type == EventType::EVNT_WRPC_FLP){
        datamodel::EncodedWorkpiece flipped_wrpc(event.payload);
        _data->wrpc_order_reset(flipped_wrpc.get_type());
        std::cout<<static_cast<int>(flipped_wrpc.get_type())<<std::endl;
    }
}

FlipHandler::~FlipHandler() {

}
} /* namespace logic */
