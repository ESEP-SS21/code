#include <dispatcher/cnnMngmnt/QnxConnection.h>
#include <errno.h>
#include <chrono>
#include <thread>

namespace dispatcher {
namespace cnnMngmnt {

// TODO call ConnectDetach() for correct resource deallocation

QnxConnection::QnxConnection(const std::string &name) {
    int retry_count = 0;
    _logger->trace("Connecting to channel '{}'", name);
    while ((_id = name_open(name.c_str(), NAME_FLAG_ATTACH_GLOBAL)) == -1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (retry_count >= 100) {
            _logger->error("Connecting to channel '{}' failed after {} attempts", name,
                    retry_count);
            break;
        }
        retry_count++;
    }
}

QnxConnection::QnxConnection(chid chid) {
    int retry_count = 0;
    while ((_id = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (retry_count >= 100) {
            _logger->error("Connecting to channel with chid '{}' failed after {} attempts", chid,
                    retry_count);
            break;
        }
        retry_count++;
    }
}

QnxConnection::~QnxConnection() {
    ConnectDetach(_id);
}

status_code QnxConnection::msg_send(iov_t *iov, int iov_size) const {
    status_code s = MsgSendvs(_id, iov, iov_size, nullptr, 0);
    if (-1 == s)
        //An error occurred (errno is set), or the server called MsgError*() (errno is set to the error value passed to MsgError()).
        _logger->error("while sending sync message");
    return s;
}

void QnxConnection::msg_send_pulse(int priority, int code, int value) const {
    if (-1 == MsgSendPulse(_id, priority, code, value)) {
        _logger->error("while sending pulse");
    }
}

}
}/* namespace dispatcher */
