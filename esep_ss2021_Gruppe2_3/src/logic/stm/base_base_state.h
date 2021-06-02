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

#define NAME_SUB(Type) const std::string Type::name = #Type##;\
std::string Type::get_name() {\
    return _substate->get_name();\
}\
std::string Type::str() {\
    return "SubSTM '" + name + "': " + _substate->get_name();\
}

#define NAME_H static const std::string name;\
std::string get_name() override;


#define ENTRY_SUB_START_NODE(Type, State) void Type::entry_sub_start_node() {\
    _substate = new State();\
    _substate->SetData(_eventSender, _datamodel);\
}\

class BaseBaseState {
protected:
    IEventSender *_eventSender;
    UnitData *_datamodel;

public:
    virtual ~BaseBaseState() = default;

    void SetData(IEventSender *eventSender,
                 datamodel::UnitData *datamodel) {
        _datamodel = datamodel;
        _eventSender = eventSender;
    }

    virtual std::string get_name() = 0;
    virtual std::string str(){
        return get_name();
    };


};

}
}
