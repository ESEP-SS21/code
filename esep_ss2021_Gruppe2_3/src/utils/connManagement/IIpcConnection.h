#ifndef SRC_UTILS_CONNMANAGEMENT_IIPCCONNECTION_H_
#define SRC_UTILS_CONNMANAGEMENT_IIPCCONNECTION_H_

#include "namespacedata"

namespace connManagement {

class IIpcConnection {
public:
    virtual ~IIpcConnection() = default;
    virtual void msg_send_pulse(int priority, int code, int value) = 0;
    virtual status_code msg_send(iov_t *iov, int iov_size, void* rmsg, int rmsg_size) = 0;
};

} /* namespace connManagement */

#endif /* SRC_UTILS_CONNMANAGEMENT_IIPCCONNECTION_H_ */
