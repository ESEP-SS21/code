/*
 * dispatcher.h
 *
 *  Created on: 05.05.2021
 *      Author: hugop
 */

#ifndef SRC_DISPATCHER_DISPATCHER_H_
#define SRC_DISPATCHER_DISPATCHER_H_
#include <thread>
#include <iostream>
#include <string>
#include <unordered_set>
#include <array>
#include <errno.h>
#include <sys/dispatch.h>
#include "../utils/connManagement/IIpcChannel.h"

namespace dispatcher {

typedef struct _pulse header_t;

class dispatcher {
public:
    dispatcher(std::unique_ptr<connManagement::IIpcChannel> ipc);
    virtual ~dispatcher();

private:
    const static int MAX_EVNT_ID { 128 };
    const std::string SERVICE_NAME { "dispatcher" };
    std::thread _dispatcher_thread;
    std::array<std::unordered_set<connManagement::conid>, MAX_EVNT_ID> _evnt_coid_map;
    bool _is_running { true };
    std::unique_ptr<connManagement::IIpcChannel> _ipc;
    void run();
    void attach();
    void handle_event(header_t header, int rcvid);
    void handle_qnx_io_msg(header_t header, int rcvid);
    void handle_event_subscr(header_t header, int rcvid);
};

} /* namespace dispatcher */

#endif /* SRC_DISPATCHER_DISPATCHER_H_ */
