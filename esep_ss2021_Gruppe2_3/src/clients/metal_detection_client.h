#pragma once
#include "logic/stm/StmMetalDetection/metal_detect_context.h"
#include "dispatcher/DispatcherClient.h"

namespace clients {

using namespace logic::stm::StmMetalDetection;

class MetalDetectionClient : public dispatcher::DispatcherClient{
public:
    MetalDetectionClient(const std::string& dispatcher_name, datamodel::UnitData * data)
    :DispatcherClient(dispatcher_name, "MetalDetectionClient"), _context(this, data) {
        subscribe( {
            EventType::EVNT_SEN_METAL_DTC,
        });
    }
    virtual ~MetalDetectionClient() = default;
protected:
    void handle(dispatcher::Event& event) {
        _context.handle(event);
    }
    MetalDetectionContext _context;
};

}
