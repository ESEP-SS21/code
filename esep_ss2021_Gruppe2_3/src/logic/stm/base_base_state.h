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
static const std::string name;\
std::string get_name() override;\
std::string str();\
void entry_sub_start_node() override;


#define INIT_OPERATING_SUB_STM(Type, EntrySubState)\
const std::string Type::name = #Type;\
std::string Type::get_name() {\
    return _operating_substate->get_name();\
}\
std::string Type::str() {\
    return "SubSTM '" + name + "': " + _operating_substate->get_name();\
}                                                                 \
void Type::entry_sub_start_node() {\
	_operating_substate = new EntrySubState();\
	_operating_substate->SetData(_eventSender, _datamodel);\
}

#define INIT_WFSTC_SUB_STM(Type, EntrySubState)\
const std::string Type::name = #Type;\
std::string Type::get_name() {\
    return _wfstc_substate->get_name();\
}\
std::string Type::str() {\
    return "SubSTM '" + name + "': " + _wfstc_substate->get_name();\
}                                                                 \
void Type::entry_sub_start_node() {\
	_wfstc_substate = new EntrySubState();\
	_wfstc_substate->SetData(_eventSender, _datamodel);\
}

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

    virtual std::string str() {
        return get_name();
    };

    virtual void entry(){};
    virtual void exit(){};

    template<typename State>
    void switch_state() {
        //todo replace with logger
        std::cout << "Exiting " << str() << std::endl;
        new (this) State;
    }


};

}
}
