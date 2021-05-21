#include "DispatcherClient.h"
#include <iostream>
#include "SyncMsg.h"
#include "Event.h"

namespace dispatcher {

DispatcherClient::DispatcherClient(const std::string& dispatcher_name, const std::string& name) :
        _name { name }, _dispatcher_name { dispatcher_name }, _channel(nullptr) {

    _channel = std::unique_ptr<cnnMngmnt::QnxChannel>(new cnnMngmnt::QnxChannel());
    _dispatcher_connection = std::unique_ptr<cnnMngmnt::QnxConnection>(
            new cnnMngmnt::QnxConnection(_dispatcher_name));
    _client_thread = std::thread([this] {this->run();});
}

DispatcherClient::~DispatcherClient() {
    _is_running = false;
    cnnMngmnt::QnxConnection(_channel->get_chid()).msg_send_pulse(1, _PULSE_CODE_UNBLOCK, 0);
    _client_thread.join();
}

void DispatcherClient::subscribe(std::initializer_list<EventType> event_types) {
    for (auto event_type : event_types){
        subscribe(event_type);
    }
}

void DispatcherClient::subscribe(EventType event_type) {
    cnnMngmnt::header_t header;

    header.type = static_cast<_Uint16t>(SyncMsgType::SUBSCRIBE);
    header.subtype = 0x00;

    EventSubscription sub { event_type, _channel->get_chid() };

    iov_t iov[2];


    SETIOV(iov + 0, &header, sizeof(header));
    SETIOV(iov + 1, &sub, sizeof(sub));
    if (-1 == _dispatcher_connection->msg_send(iov, 2)) {
        perror("Client: MsgSend failed");
        exit(EXIT_FAILURE);
    }
    const std::string t = fmt::format("Client '{}' subscr to", _name);
    _logger->trace(LOG_FORMAT2, t, str(event_type));

}

void DispatcherClient::send(Event event, int priority) const {
    int code = static_cast<int>(event.type);
    //add broadcast flag
    if (event.broadcast) {
        code = code | 0b01000000;
    }
    _dispatcher_connection->msg_send_pulse(priority, code, event.payload);
    const std::string t = fmt::format("Client '{}' send", _name);
    _logger->debug(LOG_FORMAT2, t, event.str());
}

void DispatcherClient::run() {
    while (_is_running) {
        cnnMngmnt::header_t header;
        cnnMngmnt::MsgType msg_type = _channel->msg_receive(&header, sizeof(cnnMngmnt::header_t));

        if (msg_type == cnnMngmnt::MsgType::error) {
            _logger->error("Client '{}' received error '{}'", _name, header.type);
            break;
        }

        if (msg_type == cnnMngmnt::MsgType::puls) {
            if (header.code == _PULSE_CODE_UNBLOCK) {
                continue;
            }

            Event e(header);
            const std::string t = fmt::format("Client '{}' received", _name);
            _logger->debug(LOG_FORMAT2, t, e.str());
            handle(e);
            continue;
        }

        //else sync msg

        if ((_IO_BASE <= header.type) && (header.type <= _IO_MAX)) {
            // Some QNX IO msg generated by gns was received
            handle_qnx_io_msg(header);
            continue;
        }
        // TODO handling for unsupported sync message
    }
}

void DispatcherClient::handle_qnx_io_msg(cnnMngmnt::header_t header) {
    if (header.type == _IO_CONNECT) {
        // QNX IO msg _IO_CONNECT was received; answer with EOK
        _channel->msg_reply(EOK);
        const std::string t = fmt::format("Client '{}' received", _name);
        _logger->trace(LOG_FORMAT2, t, "_IO_CONNECT");
        return;
    }
    // Some other QNX IO message was received; reject it
    _logger->critical("Client '{}' received unexpected (sync.) msg type '{}'", _name,
            header.type);
    _channel->msg_reply_error(ENOSYS);
}

} /* namespace dispatcher */
