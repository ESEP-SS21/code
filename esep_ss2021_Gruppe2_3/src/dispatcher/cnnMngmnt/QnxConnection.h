#pragma once

#include "namespacedata"
#include <string>

namespace dispatcher {
namespace cnnMngmnt {

class QnxConnection {
public:
    QnxConnection(const std::string &name);
    QnxConnection(cnnMngmnt::chid chid);
    virtual ~QnxConnection() = default;

    void msg_send_pulse(int priority, int code, int value) const;
    status_code msg_send(iov_t *iov, int iov_size, void* rmsg, int rmsg_size) const;

private:
    int _id;
};

}
} /* namespace connManagement */
