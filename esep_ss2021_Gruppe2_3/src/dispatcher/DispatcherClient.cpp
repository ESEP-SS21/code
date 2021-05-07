#include <dispatcher/DispatcherClient.h>
#include <sys/dispatch.h>
#include <iostream>

namespace dispatcher {

DispatcherClient::DispatcherClient(const std::string& disp_name,
        std::unique_ptr<cnnMngmnt::QnxChannel> channel) :
        _dispatcher_name { disp_name }, _channel(std::move(channel)) {
    _dispatcher_connection = std::unique_ptr<cnnMngmnt::QnxConnection>(
            new cnnMngmnt::QnxConnection(_dispatcher_name));
    _client_thread = std::thread([this] {this->run();});
}

DispatcherClient::~DispatcherClient() {
    _is_running = false;
    cnnMngmnt::QnxConnection(_channel->get_chid()).msg_send_pulse(1, _PULSE_CODE_UNBLOCK, 0);
    _client_thread.join();
}

void DispatcherClient::subscribe_evnt(uint8_t evnt_nr) {
    cnnMngmnt::header_t header;

    header.type = SUB_MSG;
    header.subtype = 0x00;

    EventSubscription sub;
    sub.channel_id = _channel->get_chid();
    sub.number = evnt_nr;

    iov_t iov[2];
    int r_msg;
    SETIOV(iov + 0, &header, sizeof(header));
    SETIOV(iov + 1, &sub, sizeof(sub));
    if (-1 == _dispatcher_connection->msg_send(iov, 2, &r_msg, sizeof(r_msg))) {
        perror("Client: MsgSend failed");
        exit(EXIT_FAILURE);
    }
}
void DispatcherClient::send_evnt(Event event, int priority) {
    _dispatcher_connection->msg_send_pulse(priority, event.number, event.payload);
}

void DispatcherClient::run() {
    while (_is_running) {
        cnnMngmnt::header_t header;
        cnnMngmnt::MsgType msg_type = _channel->msg_receive(&header, sizeof(cnnMngmnt::header_t));

        if (msg_type == cnnMngmnt::MsgType::error) {
            //TODO logging or exception
            break;
        }

        if (msg_type == cnnMngmnt::MsgType::puls) {
            if (header.code == _PULSE_CODE_UNBLOCK) {
                continue;
            }
            handle_event(header);
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

void DispatcherClient::handle_event(cnnMngmnt::header_t header) {
    Event event;
    event.number = header.code;
    event.payload = header.value.sival_int;
    handle(event);
}

void DispatcherClient::handle_qnx_io_msg(cnnMngmnt::header_t header) {
    if (header.type == _IO_CONNECT) {
        // QNX IO msg _IO_CONNECT was received; answer with EOK
        std::cout << "Dispatcher received _IO_CONNECT (sync. msg) \n" << std::endl;
        _channel->msg_reply(EOK, nullptr, 0);
        return;
    }
    // Some other QNX IO message was received; reject it
    std::cout << "Dispatcher received unexpected (sync.) msg type = " << header.type << std::endl;
    _channel->msg_reply_error(ENOSYS);
}

} /* namespace dispatcher */
