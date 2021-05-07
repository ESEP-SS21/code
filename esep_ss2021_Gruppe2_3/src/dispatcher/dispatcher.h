#pragma once

#include <thread>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include "cnnMngmnt/QnxChannel.h"
#include "cnnMngmnt/QnxConnection.h"
namespace dispatcher {

class dispatcher {
public:
    dispatcher(const std::string &name);
    virtual ~dispatcher();

private:
    static const int MAX_EVNT_ID { 128 };
    const std::string SERVICE_NAME { "dispatcher" };

    void attach() const;
    void handle_event(cnnMngmnt::header_t header) const;
    void handle_qnx_io_msg(cnnMngmnt::header_t header) const;
    void run();
    void handle_sync_msg(cnnMngmnt::header_t header);
    void subscribe(int event_id, cnnMngmnt::chid chid);

    bool _is_running { true };
    std::thread _dispatcher_thread;
    std::unordered_map<cnnMngmnt::chid, std::shared_ptr<cnnMngmnt::QnxConnection>> _chid_conn_map { };
    std::array<std::unordered_set<std::shared_ptr<cnnMngmnt::QnxConnection>>, MAX_EVNT_ID> _evnt_conn_multimap;
    std::unique_ptr<cnnMngmnt::QnxChannel> _channel;

};

} /* namespace dispatcher */
