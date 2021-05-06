#ifndef SRC_UTILS_QNXCONNECTION_H_
#define SRC_UTILS_QNXCONNECTION_H_
#include <errno.h>
#include <string>

#include "IIpcConnection.h"

namespace connManagement {

class QnxConnection: public IIpcConnection {
public:
    virtual ~QnxConnection() = default;

    QnxConnection(const std::string &name) {
        _id = name_open(name.c_str(), NAME_FLAG_ATTACH_GLOBAL);
        if (-1 == _id)
            std::cout << "error while connecting to channel via name" << std::endl;
    }

    QnxConnection(connManagement::chid chid) {
        _id = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
        if (-1 == _id)
            std::cout << "error while connecting to channel via chid" << std::endl;
    }

    connManagement::status_code msg_send(void* smsg, int smsg_size, void* rmsg, int rmsg_size) {
        status_code s = MsgSend(_id, smsg, smsg_size, rmsg, rmsg_size);
        if (-1 == s)
            //An error occurred (errno is set), or the server called MsgError*() (errno is set to the error value passed to MsgError()).
            std::cout << "error while sending" << std::endl;
        return s;
    }

    void msg_send_pulse(int priority, int code, int value) {
        if (-1 == MsgSendPulse(_id, priority, code, value)) {
            std::cout << "error while sending puls" << std::endl;
            std::cout << "log(-1) failed: " << errno << '\n';
        }
    }

private:
    int _id;
};

} /* namespace dispatcher */

#endif /* SRC_UTILS_QNXCONNECTION_H_ */
