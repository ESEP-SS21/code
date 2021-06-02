#pragma once

namespace dispatcher {
namespace cnnMngmnt {

union sigval {
    int sival_int;
    void *sival_ptr;
};

struct custom_header_t {
    uint16_t type;
    uint16_t subtype;
    int8_t code;
    uint8_t zero[3];
    union sigval value;
    int32_t scoid;
};

using rcvid = int;
using chid = int;
using status_code = int;
using conid = int;

} /* namespace */
} /* namespace */

#define LOG_FORMAT2 "{:<33} '{}'"
