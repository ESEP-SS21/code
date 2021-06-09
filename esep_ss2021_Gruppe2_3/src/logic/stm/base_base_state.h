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
STATE_HEADER_INIT \
std::string str();\

#define INIT_SUB_STM(Type, EntrySubState, SubStmName)\
const std::string Type::name = #Type;\
std::string Type::get_name() const {\
    return SubStmName->get_name();\
}\
std::string Type::str() {\
    return "SubSTM '" + name + "': " + SubStmName->get_name();\
}                                                                 \

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

    virtual void init_sub_states(){};

    virtual std::string str() {
        return get_name();
    };

    virtual void entry(){};
    virtual void exit(){};

    template<typename State>
    void switch_state() {
        std::cout << " [" << _context_name << "] " << "Exiting " << str() << std::endl;
                new (this) State;
    }
};

}
}
