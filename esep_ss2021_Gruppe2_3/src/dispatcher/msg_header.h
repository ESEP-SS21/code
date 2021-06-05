#pragma once

#include <sys/dispatch.h>
#include "cnnMngmnt/namespacedata.h"
using namespace dispatcher;
struct header_t {
    _Uint16t type;
    _Uint16t subtype;
    _Int8t code;
    _Uint8t zero[3];
    union cnnMngmnt::sigval value;
    _Int32t scoid;
    cnnMngmnt::custom_header_t convert_to_custom(){
        return cnnMngmnt::custom_header_t{
             type,
             subtype,
             code,
             value
        };
    }
};
