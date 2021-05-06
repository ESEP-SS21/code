#ifndef SRC_DISPATCHER_DISPATCHER_H_
#define SRC_DISPATCHER_DISPATCHER_H_
#include <thread>
#include <iostream>
#include <string>
#include <unordered_set>
#include <array>
#include "../utils/connManagement/QnxChannel.h" //TODO use the interface instead. This needs a 'IIpcConnectionFactory of some sort'
#include "../utils/connManagement/QnxConnection.h"

namespace dispatcher {

class dispatcher {
public:
    dispatcher(std::unique_ptr<connManagement::IIpcChannel> ipc);
    virtual ~dispatcher();

private:
    const static int MAX_EVNT_ID { 128 };
    const std::string SERVICE_NAME { "dispatcher" };
    std::thread _dispatcher_thread;
    std::array<std::unordered_set<std::unique_ptr<connManagement::IIpcConnection>>, MAX_EVNT_ID> _evnt_coid_map;
    bool _is_running { true };
    std::unique_ptr<connManagement::IIpcChannel> _ipc;
    void run();
    void attach();
    void handle_event(connManagement::header_t header, int rcvid);
    void handle_qnx_io_msg(connManagement::header_t header, int rcvid);
    void handle_event_subscr(connManagement::header_t header, int rcvid);
};

} /* namespace dispatcher */

#endif /* SRC_DISPATCHER_DISPATCHER_H_ */
