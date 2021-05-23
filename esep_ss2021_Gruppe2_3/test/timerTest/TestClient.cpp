#include <timerTest/TestClient.h>

using namespace dispatcher;
namespace test {
namespace timerTest {

TestClient::TestClient(const std::string& dispatcher_name, const std::string& name) :
        _name { name }, _dispatcher_name { dispatcher_name }, _channel(nullptr) {

    _channel = std::unique_ptr<cnnMngmnt::QnxChannel>(new cnnMngmnt::QnxChannel());
    _dispatcher_connection = std::unique_ptr<cnnMngmnt::QnxConnection>(
            new cnnMngmnt::QnxConnection(_dispatcher_name));
}

TestClient::TestClient::~TestClient() {

}

void TestClient::subscribe(std::initializer_list<dispatcher::EventType> event_types) {
    for (auto event_type : event_types) {
        subscribe(event_type);
    }
}

void TestClient::subscribe(dispatcher::EventType event_type) {
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
}

void TestClient::send(Event event, int priority) const {
    int code = static_cast<int>(event.type);
    //add broadcast flag
    if (event.broadcast) {
        code = code | 0b01000000;
    }
    _dispatcher_connection->msg_send_pulse(priority, code, event.payload);
}

Event TestClient::recieve_event() {
    cnnMngmnt::header_t header;
    _channel->msg_receive(&header, sizeof(cnnMngmnt::header_t));
    Event e(header);
    return e;
}

} /*namespace*/
} /*namespace*/
