#include "cnnMngmnt/QnxConnection.h"
#include "Dispatcher.h"
#include <errno.h>
#include "Event.h"
#include "SyncMsg.h"

namespace dispatcher {

Dispatcher::Dispatcher(const std::string &name) :
        _channel(std::unique_ptr<cnnMngmnt::QnxChannel>(new cnnMngmnt::QnxChannel(name))) {
    _dispatcher_thread = std::thread([this] {this->run();});
    _other_connection.reset();
}

Dispatcher::~Dispatcher() {
    _is_running = false;
    cnnMngmnt::QnxConnection(_channel->get_chid()).msg_send_pulse(1, _PULSE_CODE_UNBLOCK, 0);
    _dispatcher_thread.join();
}

void Dispatcher::connect_to_other(const std::string &other_dispacher_name) {
    _other_connection = std::unique_ptr<cnnMngmnt::QnxConnection>(
            new cnnMngmnt::QnxConnection(other_dispacher_name));
}

void Dispatcher::run() {
    while (_is_running) {
        cnnMngmnt::header_t header;
        cnnMngmnt::MsgType type = _channel->msg_receive(&header, sizeof(cnnMngmnt::header_t));

        if (type == cnnMngmnt::MsgType::error) {
            _logger->error("Dispatcher received error '{}'", header.type);
            break;
        }

        if (type == cnnMngmnt::MsgType::puls) {
            if (header.code < 0) {
                continue;
            }

            Event e(header);
            dispatch(e);
            continue;
        }

        //else type == sync

        if ((_IO_BASE <= header.type) && (header.type <= _IO_MAX)) {
            // Some QNX IO msg generated by gns was received
            handle_qnx_io_msg(header);
            continue;
        }
        handle_sync_msg(header);
    }
}

void Dispatcher::handle_sync_msg(cnnMngmnt::header_t header) {
    if (SyncMsgType::SUBSCRIBE == SyncMsgType(header.type)) {

        EventSubscription subscription;
        _channel->msg_read(&subscription, sizeof(subscription), sizeof(header));
        subscribe(subscription);
        _channel->msg_reply(EOK);

        _logger->trace(LOG_FORMAT2, "Dispatcher received subscr for", str(subscription.type));
    }
    //maybe other forms of sync communications
}

void Dispatcher::subscribe(EventSubscription subscr) {
    if (_chid_conn_map.find(subscr.chid) == _chid_conn_map.end()) {
        //no connection for this chid yet, create a new one
        _chid_conn_map[subscr.chid] = std::shared_ptr<cnnMngmnt::QnxConnection>(
                new cnnMngmnt::QnxConnection(subscr.chid));
    }
    _subscriptons[static_cast<int>(subscr.type)].insert(_chid_conn_map[subscr.chid]);
}

void Dispatcher::dispatch(Event e) const {
    int evnt_id = static_cast<int> (e.type);
    _logger->trace(LOG_FORMAT2, "Dispatcher received", e.str());

    if (e.broadcast && _other_connection != nullptr) {
        int payload = e.payload;
        if(e.type == EventType::EVNT_ERR){
            // Clear payload, as the payload of the ERR event is the EventType
            // which needs to be received to mark the as fixed. Thus receiving that
            // specific Event is only allowed at the FBS on which the error was caused at.
            payload = 0;
        }
        int ret_code = _other_connection->msg_send_pulse(1, evnt_id, payload);
        if(ret_code == -1){
            Event conn_lost_evnt = { EventType::EVNT_CONN_LOST, 0, false };
            dispatch(conn_lost_evnt);
        }
        _logger->trace(LOG_FORMAT2, "Dispatcher broadcasted", e.str());
    }

    for (auto& connection : _subscriptons[evnt_id]) {
        connection->msg_send_pulse(1, evnt_id, e.payload);
    }
    _logger->trace(LOG_FORMAT2, "Dispatcher dispatched", e.str());
}

void Dispatcher::handle_qnx_io_msg(cnnMngmnt::header_t header) const {
    if (header.type == _IO_CONNECT) {
        _channel->msg_reply(EOK);
        _logger->trace(LOG_FORMAT2, "Dispatcher received", "_IO_CONNECT");
        return;
    }
    _logger->error("Dispatcher received unexpected sync. QNX IO with type '{}'", header.type);
    _channel->msg_reply_error(ENOSYS);
}

} /* namespace dispatcher */
