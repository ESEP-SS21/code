#pragma once

#include <string>
#include "dispatcher/IEventSender.h"
#include "../datamodel/unit_data.h"

#define nextState(State) new(this) State(std::move(_eventSender), std::move(_datamodel))

#define Ctor(Type) Type(std::shared_ptr<IEventSender> eventSender, std::shared_ptr<UnitData> datamodel) \
: TestBaseState(name, std::move(eventSender), std::move(datamodel)) {}

namespace logic {
namespace stm {

using namespace dispatcher;
using namespace datamodel;

class BaseBaseState {
protected:
    const std::string _name;
    std::shared_ptr<IEventSender> _eventSender;
    std::shared_ptr<UnitData> _datamodel;

public:
    BaseBaseState(const std::string &name, std::shared_ptr<IEventSender> eventSender,
                  std::shared_ptr<UnitData> datamodel)
        : _name(name), _eventSender(eventSender), _datamodel(datamodel) {}

    virtual ~BaseBaseState() = default;

    std::string get_name() {
        return _name;
    }


};

}
}
