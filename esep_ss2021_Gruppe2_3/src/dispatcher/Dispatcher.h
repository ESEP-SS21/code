#pragma once

#include <sys/dispatch.h>
#include <thread>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include "cnnMngmnt/QnxChannel.h"
#include "cnnMngmnt/QnxConnection.h"
#include "Event.h"
#include "msg_header.h"

namespace dispatcher {

class Dispatcher {
public:
    Dispatcher(const std::string &name);
    void connect_to_other(const std::string &other_dispacher_name);
    virtual ~Dispatcher();

private:
    void run();
    void subscribe(EventSubscription subscr);
    void dispatch(Event e) const;
    void handle_sync_msg(header_t header);
    void handle_qnx_io_msg(header_t header) const;

    Logger::Logger _logger { Logger::get() };
    bool _is_running { true };
    std::thread _dispatcher_thread;
    std::unordered_map<cnnMngmnt::chid, std::shared_ptr<cnnMngmnt::QnxConnection>> _chid_conn_map { };
    /**
     * Multimap of subscriptions.
     * The array is indexed by the EventType Enum, which returns a set of QnxConnections.
     * These represent all the QnxConnections which are subscribed to said EventType.
     */
    std::array<std::unordered_set<std::shared_ptr<cnnMngmnt::QnxConnection>>, static_cast<int>(EventType::SIZE)> _subscriptons;
    std::unique_ptr<cnnMngmnt::QnxChannel> _channel;
    std::unique_ptr<cnnMngmnt::QnxConnection> _other_connection;
};

} /* namespace dispatcher */
