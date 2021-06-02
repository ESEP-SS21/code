#pragma once

#include <string>
#include "dispatcher/IEventSender.h"

namespace logic {
namespace stm {

using namespace dispatcher;

class BaseBaseState {
protected:
    const std::string _name;
    std::shared_ptr<IEventSender> _eventSender;

public:
    BaseBaseState(const std::string &name, std::shared_ptr<IEventSender> eventSender)
        : _name(name), _eventSender(eventSender) {}

    virtual ~BaseBaseState() = default;

    std::string get_name() {
        return _name;
    }


};

}
}
