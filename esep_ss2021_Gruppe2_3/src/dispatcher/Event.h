#pragma once

namespace dispatcher {

#define SUB_MSG   (_IO_MAX + 1)

struct Event {
    int number;
    int payload;
};

struct EventSubscription {
    int number;
    int channel_id;
};
}
