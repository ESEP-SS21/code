/*
 * Event.h
 *
 *  Created on: 07.05.2021
 *      Author: jendr
 */
#ifndef SRC_DISPATCHER_EVENT_H_
#define SRC_DISPATCHER_EVENT_H_

namespace dispatcher{

#define SUB_MSG   (_IO_MAX + 1)

struct Event
{
    int number;
    int payload;
};

struct EventSubscription{
    int number;
    int channel_id;
};
}
#endif /* SRC_DISPATCHER_EVENT_H_ */
