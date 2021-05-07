#ifndef SRC_DISPATCHER_DISPATCHERCLIENT_H_
#define SRC_DISPATCHER_DISPATCHERCLIENT_H_

#include <string>
#include <thread>
#include "../utils/connManagement/QnxChannel.h" //TODO use the interface instead. This needs a 'IIpcConnectionFactory of some sort'
#include "../utils/connManagement/QnxConnection.h"
#include "Event.h"

namespace dispatcher {

class DispatcherClient {
public:
    DispatcherClient(const std::string& disp_name, std::unique_ptr<connManagement::QnxChannel> channel);
    virtual ~DispatcherClient();
    void subscribe_evnt(uint8_t evnt_nr);
    void send_evnt(Event event, int prio);
    virtual void handle(Event&)=0;

private:
    void run();
    void recieve_evnt(Event * event);
    void handle_event(connManagement::header_t header);
    void handle_qnx_io_msg(connManagement::header_t header);
    std::string _dispatcher_name;
    std::unique_ptr<connManagement::QnxChannel> _channel;
    std::unique_ptr<connManagement::QnxConnection> _dispatcher_connection;
    bool _is_running { true };
    std::thread _client_thread;
};

} /* namespace dispatcher */

#endif /* SRC_DISPATCHER_DISPATCHERCLIENT_H_ */
