#ifndef SRC_DISPATCHER_DISPATCHER_H_
#define SRC_DISPATCHER_DISPATCHER_H_
#include <thread>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include "connManagement/QnxChannel.h" //TODO use the interface instead. This needs a 'IIpcConnectionFactory of some sort'
#include "connManagement/QnxConnection.h"
#include "Event.h"
namespace dispatcher {

class dispatcher {
public:
    dispatcher(std::unique_ptr<cnnMngmnt::QnxChannel> ipc);
    virtual ~dispatcher();

private:
    const static int MAX_EVNT_ID { 128 };
    const std::string SERVICE_NAME { "dispatcher" };
    std::thread _dispatcher_thread;
    std::unordered_map<cnnMngmnt::chid, std::shared_ptr<cnnMngmnt::QnxConnection>> _chid_conn_map { };
    std::array<std::unordered_set<std::shared_ptr<cnnMngmnt::QnxConnection>>, MAX_EVNT_ID> _evnt_conn_multimap;
    bool _is_running { true };
    std::unique_ptr<cnnMngmnt::QnxChannel> _channel;
    void run();
    void attach();
    void handle_event(cnnMngmnt::header_t header);
    void handle_qnx_io_msg(cnnMngmnt::header_t header);
    void handle_sync_msg(cnnMngmnt::header_t header);
    void subscribe(int event_id, cnnMngmnt::chid chid);
};

} /* namespace dispatcher */

#endif /* SRC_DISPATCHER_DISPATCHER_H_ */
