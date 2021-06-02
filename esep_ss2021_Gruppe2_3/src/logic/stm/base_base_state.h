#pragma once

#include <string>
#include "dispatcher/IEventSender.h"
#include "../datamodel/unit_data.h"

namespace logic {
namespace stm {

using namespace dispatcher;
using namespace datamodel;

class BaseBaseState {
protected:
    IEventSender* _eventSender;
    UnitData* _datamodel;

public:
    virtual ~BaseBaseState() = default;

    void SetData(IEventSender* eventSender,
                 datamodel::UnitData* datamodel) {
        _datamodel = datamodel;
        _eventSender = eventSender;
    }

    virtual std::string get_name() = 0;


};

}
}
