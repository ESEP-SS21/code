#pragma once

#include <string>
#include "dispatcher/IEventSender.h"
#include "../datamodel/unit_data.h"

namespace logic {
namespace stm {

using namespace dispatcher;
using namespace datamodel;

#define STATE_INIT(Type)\
const std::string Type::name = #Type;\
std::string Type::get_name() const {\
    return name;\
}

#define STATE_HEADER_INIT \
static const std::string name;\
std::string get_name() const override;

#define SUBSTM_HEADER_INIT \
static const std::string name;\
std::string get_name() const override;\
std::string str();\
void entry_sub_start_node() override;


#define INIT_OPERATING_SUB_STM(Type, EntrySubState)\
const std::string Type::name = #Type;\
std::string Type::get_name() const {\
    return _operating_substate->get_name();\
}\
std::string Type::str() {\
    return "SubSTM '" + name + "': " + _operating_substate->get_name();\
}                                                                 \
void Type::entry_sub_start_node() {\
    _operating_substate = new EntrySubState();\
    _operating_substate->SetData(_eventSender, _datamodel, #Type);\
}

#define INIT_WFSTC_SUB_STM(Type, EntrySubState)\
const std::string Type::name = #Type;\
std::string Type::get_name() const {\
    return _wfstc_substate->get_name();\
}\
std::string Type::str() {\
    return "SubSTM '" + name + "': " + _wfstc_substate->get_name();\
}                                                                 \
void Type::entry_sub_start_node() {\
    _wfstc_substate = new EntrySubState();\
    _wfstc_substate->SetData(_eventSender, _datamodel, #Type);\
}

class BaseBaseState {
protected:
    //Destructor of members will be called on state switch,
    // due to new(this) -> do not use smart pointers or containers here
    IEventSender *_eventSender;
    UnitData *_datamodel;
    char* _context_name;

public:
    virtual ~BaseBaseState() = default;

    //TODO make this virtual once everybody uses this
    virtual bool handle(const Event &event) {return false;}

    void SetData(IEventSender *eventSender,
                 datamodel::UnitData *datamodel,
                 char* contextName) {
        _datamodel = datamodel;
        _eventSender = eventSender;
        _context_name = contextName;
    }

    virtual std::string get_name() const = 0;

    virtual std::string str() const {
        return get_name();
    };

    template<typename State>
    void switch_state() {
        //todo replace with logger
        const std::string old_state = str();
        new(this) State;
        std::cout << "["<<_context_name<< "] " << old_state << " -> " << str() << std::endl;
    }
};

}
}
