#ifndef SRC_UTILS_CONNMANAGEMENT_QNXCONNECTION_H_
#define SRC_UTILS_CONNMANAGEMENT_QNXCONNECTION_H_

#include "namespacedata"
#include <string>

namespace connManagement {

class QnxConnection {
public:
    virtual ~QnxConnection() = default;
    QnxConnection(const std::string &name);
    QnxConnection(connManagement::chid chid);
    void msg_send_pulse(int priority, int code, int value);
    status_code msg_send(iov_t *iov, int iov_size, void* rmsg, int rmsg_size);
private:
    int _id;
};

} /* namespace connManagement */

#endif /* SRC_UTILS_CONNMANAGEMENT_QNXCONNECTION_H_ */
