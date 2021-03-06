#pragma once

#include <string>
#include <thread>
#include "cnnMngmnt/QnxChannel.h" //TODO use the interface instead. This needs a 'IIpcConnectionFactory of some sort'
#include "cnnMngmnt/QnxConnection.h"
#include "Event.h"
#include "IEventSender.h"
#include "msg_header.h"

namespace dispatcher {

class DispatcherClient : public IEventSender {
public:
    DispatcherClient(const std::string& dispatcher_name, const std::string& name);
    virtual ~DispatcherClient();
    void send(Event event, int prio = 0);
    void subscribe(EventType event_type);
    void subscribe(std::initializer_list<EventType> event_types);

protected:
    std::unique_ptr<cnnMngmnt::QnxConnection> _dispatcher_connection;
    Logger::Logger _logger { Logger::get() };

private:
    void run();
    void handle_qnx_io_msg(header_t header);
    virtual void handle(Event&) = 0;

    bool _is_running { true };
    std::string _name;
    std::string _dispatcher_name;
    std::unique_ptr<cnnMngmnt::QnxChannel> _channel;

    std::thread _client_thread;
};

} /* namespace dispatcher */
