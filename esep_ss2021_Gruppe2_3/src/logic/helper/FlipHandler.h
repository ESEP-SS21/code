#pragma once

#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"
#include "logic/datamodel/unit_data.h"
#include "logic/datamodel/encoded_workpiece.h"

namespace logic {

class FlipHandler: public dispatcher::DispatcherClient {
public:
    FlipHandler(const std::string& dispatcher_name, std::shared_ptr<logic::datamodel::UnitData> data);
    virtual ~FlipHandler();

private:
    std::shared_ptr<logic::datamodel::UnitData> _data;
    void handle(dispatcher::Event& event) override;
    Logger::Logger _logger { Logger::get() };
};

} /* namespace logic */

