#include <dispatcher/cnnMngmnt/QnxConnection.h>
#include <dispatcher/Dispatcher.h>
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

void Dispatcher::connect_to_other(const std::string &name){
    _other_connection = std::unique_ptr<cnnMngmnt::QnxConnection>(
            new cnnMngmnt::QnxConnection(name));
}

void Dispatcher::run() {
    while (_is_running) {
        cnnMngmnt::header_t header;
        cnnMngmnt::MsgType type = _channel->msg_receive(&header, sizeof(cnnMngmnt::header_t));

        if (type == cnnMngmnt::MsgType::error) {
            //TODO logging or exception
            break;
        }

        if (type == cnnMngmnt::MsgType::puls) { // Pulse was received
            if (header.code == _PULSE_CODE_UNBLOCK) {
                continue;
            }
            handle_event(header);
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

        _logger->trace("Dispatcher subscribed to '{}'", str(subscription.type));
    }
    //maybe other forms of sync communications
}

void Dispatcher::subscribe(EventSubscription subscr) {
    if (_chid_conn_map.find(subscr.chid) == _chid_conn_map.end()) { //no connection for this chid yet
        _chid_conn_map[subscr.chid] = std::shared_ptr<cnnMngmnt::QnxConnection>(
                new cnnMngmnt::QnxConnection(subscr.chid));
    }
    _evnt_conn_multimap[static_cast<int>(subscr.type)].insert(_chid_conn_map[subscr.chid]);
}

void Dispatcher::handle_event(cnnMngmnt::header_t header) const {
    int evnt_id = header.code;
    int evnt_value = header.value.sival_int;
    if(evnt_id<0){
        return;
    }
    if ((evnt_id & 0b01000000) != 0) {
        // mask out transmission bit if message is for other dispatcher
        evnt_id = evnt_id & (~0b01000000);
        if (_other_connection.get() != nullptr) {
            // send event to other dispatcher if not in single mode
            _other_connection->msg_send_pulse(1, evnt_id, evnt_value);
        }
    }

    _logger->trace("Dispatcher received: '{}'", Event(header, false).str());

    for (auto& connection : _evnt_conn_multimap[evnt_id]) {
        connection->msg_send_pulse(1, evnt_id, evnt_value);
    }
}

void Dispatcher::handle_qnx_io_msg(cnnMngmnt::header_t header) const {
    if (header.type == _IO_CONNECT) {
        // QNX IO msg _IO_CONNECT was received; answer with EOK
        _logger->trace("Dispatcher received _IO_CONNECT");
        _channel->msg_reply(EOK);
        return;
    }
    // Some other QNX IO message was received; reject it
    _logger->error("Dispatcher received unexpected (sync.) msg type '{}'", header.type);
    _channel->msg_reply_error(ENOSYS);
}

} /* namespace dispatcher */
