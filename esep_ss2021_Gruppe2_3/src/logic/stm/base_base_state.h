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
std::string Type::get_name() {\
    return name;\
}

#define STATE_HEADER_INIT \
static const std::string name;\
std::string get_name() override;

#define SUBSTM_HEADER_INIT \
STATE_HEADER_INIT \
std::string str();\

#define INIT_SUB_STM(Type, EntrySubState, SubStmName)\
const std::string Type::name = #Type;\
std::string Type::get_name() {\
    return SubStmName->get_name();\
}\
std::string Type::str() {\
    return "SubSTM '" + name + "': " + SubStmName->get_name();\
}                                                                 \

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

    virtual void init_sub_states(){};

    virtual std::string str() {
        return get_name();
    };

    template<typename State>
    void switch_state() {
        //todo replace with logger
        std::cout << "Exiting " << str() << std::endl;
        new (this) State;
    }


};

}
}
