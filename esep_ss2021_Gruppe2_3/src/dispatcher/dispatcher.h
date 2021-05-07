#ifndef SRC_DISPATCHER_DISPATCHER_H_
#define SRC_DISPATCHER_DISPATCHER_H_
#include <thread>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include "../utils/connManagement/QnxChannel.h" //TODO use the interface instead. This needs a 'IIpcConnectionFactory of some sort'
#include "../utils/connManagement/QnxConnection.h"
#include "Event.h"
namespace dispatcher {

class dispatcher {
public:
    dispatcher(std::unique_ptr<connManagement::IIpcChannel> ipc);
    virtual ~dispatcher();

private:
    const static int MAX_EVNT_ID { 128 };
    const std::string SERVICE_NAME { "dispatcher" };
    std::thread _dispatcher_thread;
    std::unordered_map<connManagement::chid, std::shared_ptr<connManagement::IIpcConnection>> _chid_conn_map {};
    std::array<std::unordered_set<std::shared_ptr<connManagement::IIpcConnection>>, MAX_EVNT_ID> _evnt_conn_multimap;
    bool _is_running { true };
    std::unique_ptr<connManagement::IIpcChannel> _channel;
    void run();
    void attach();
    void handle_event(connManagement::header_t header);
    void handle_qnx_io_msg(connManagement::header_t header );
    void handle_sync_msg(connManagement::header_t header  );
    void subscribe(int event_id, connManagement::chid chid);
};

} /* namespace dispatcher */

#endif /* SRC_DISPATCHER_DISPATCHER_H_ */
