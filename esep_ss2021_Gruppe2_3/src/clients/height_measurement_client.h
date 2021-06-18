#pragma once
#include "logic/stm/StmHeightMeasurement/height_measurement_context.h"
#include "dispatcher/DispatcherClient.h"

namespace clients {

using namespace logic::stm::StmHeightMeasurement;

class HeightMeasurementClient : public dispatcher::DispatcherClient{
public:
    HeightMeasurementClient(const std::string& dispatcher_name, datamodel::UnitData * data)
    :DispatcherClient(dispatcher_name, "HeightMeasurementClient"), _context(this, data) {
        subscribe( {
            EventType::EVNT_HIST,
            EventType::EVNT_RST_TO_SRT,
            EventType::EVNT_SEN_HEIGHT_HE,
            EventType::EVNT_SEN_LB_HE_BLCK
        });
    }
    virtual ~HeightMeasurementClient() = default;
protected:
    void handle(dispatcher::Event& event) {
        _context.handle(event);
    }
    HeightMeasurementContext _context;
};

}
