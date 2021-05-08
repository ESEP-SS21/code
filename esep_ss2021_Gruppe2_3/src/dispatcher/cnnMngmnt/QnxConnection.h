#pragma once

#include "namespacedata"
#include <string>

namespace dispatcher {
namespace cnnMngmnt {

class QnxConnection {
public:
    QnxConnection(const std::string &name);
    QnxConnection(cnnMngmnt::chid chid);
    virtual ~QnxConnection();

    void msg_send_pulse(int priority, int code, int value) const;
    status_code msg_send(iov_t *iov, int iov_size) const;

private:
    int _id;
};

}
} /* namespace connManagement */
