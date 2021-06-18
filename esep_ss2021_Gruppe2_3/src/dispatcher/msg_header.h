#pragma once

#include <sys/dispatch.h>
#include "connection_management/namespacedata.h"
using namespace dispatcher;
struct header_t {
    _Uint16t type;
    _Uint16t subtype;
    _Int8t code;
    _Uint8t zero[3];
    union connection_management::sigval value;
    _Int32t scoid;
    connection_management::custom_header_t convert_to_custom(){
        return connection_management::custom_header_t{
             type,
             subtype,
             code,
             value
        };
    }
};
