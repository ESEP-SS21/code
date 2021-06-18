#pragma once

#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"
#include "logic/datamodel/unit_data.h"
#include "logic/datamodel/encoded_workpiece.h"

namespace clients {

class FlipHandlerClient: public dispatcher::DispatcherClient {
public:
    FlipHandlerClient(const std::string& dispatcher_name, std::shared_ptr<logic::datamodel::UnitData> data);
    virtual ~FlipHandlerClient() = default;

private:
    std::shared_ptr<logic::datamodel::UnitData> _data;
    void handle(dispatcher::Event& event) override;
    Logger::Logger _logger { Logger::get() };
};

}
