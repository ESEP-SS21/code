#pragma once

#include <string>
#include "dispatcher/IEventSender.h"
#include "../datamodel/unit_data.h"

namespace logic {
namespace stm {

using namespace dispatcher;
using namespace datamodel;

#define NAME(Type) const std::string Type::name = #Type##;\
std::string Type::get_name() {\
    return name;\
}

#define NAME_H static const std::string name;\
std::string get_name() override;


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
