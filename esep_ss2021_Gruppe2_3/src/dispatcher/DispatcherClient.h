#ifndef SRC_DISPATCHER_DISPATCHERCLIENT_H_
#define SRC_DISPATCHER_DISPATCHERCLIENT_H_

#include <string>
#include <thread>
#include "cnnMngmnt/QnxChannel.h" //TODO use the interface instead. This needs a 'IIpcConnectionFactory of some sort'
#include "cnnMngmnt/QnxConnection.h"
#include "Event.h"

namespace dispatcher {

class DispatcherClient {
public:
    DispatcherClient(const std::string& name);
    virtual ~DispatcherClient();
    void subscribe_evnt(uint8_t evnt_nr);
    void send_evnt(Event event, int prio);
    virtual void handle(Event&)=0;

private:
    void run();
    void recieve_evnt(Event * event);
    void handle_event(cnnMngmnt::header_t header);
    void handle_qnx_io_msg(cnnMngmnt::header_t header);
    std::string _dispatcher_name;
    std::unique_ptr<cnnMngmnt::QnxChannel> _channel;
    std::unique_ptr<cnnMngmnt::QnxConnection> _dispatcher_connection;
    bool _is_running { true };
    std::thread _client_thread;
};

} /* namespace dispatcher */

#endif /* SRC_DISPATCHER_DISPATCHERCLIENT_H_ */
