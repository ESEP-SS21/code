#pragma once

#include <stdint.h>

namespace dispatcher {
namespace connection_management {

union sigval {
    int sival_int;
    void *sival_ptr;
};

struct custom_header_t {
    uint16_t type;
    uint16_t subtype;
    int8_t code;
    union sigval value;
};

using rcvid = int;
using chid = int;
using status_code = int;
using conid = int;

} /* namespace */
} /* namespace */

#define LOG_FORMAT2 "{:<33} '{}'"
