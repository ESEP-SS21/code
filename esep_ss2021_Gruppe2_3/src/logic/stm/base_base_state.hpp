#pragma once

#include <string>
#include <dispatcher/IEventSender.h>

namespace logic {
namespace stm {
namespace testStm {

using namespace dispatcher;

class BaseBaseState {
protected:
    const std::string _name;
    std::shared_ptr<IEventSender> eventSender;

public:
    BaseBaseState(const std::string &name) : _name(name) {}

    virtual ~BaseBaseState() = default;

    std::string get_name() {
        return _name;
    }


};

}
}

}