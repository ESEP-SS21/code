#ifndef SRC_DISPATCHER_IIPC_H_
#define SRC_DISPATCHER_IIPC_H_

#include "namespacedata"

namespace connManagement {

class IIpcChannel {
public:
    virtual ~IIpcChannel() = default;
    virtual rcvid msg_receive(void* msg, int size) = 0;
    virtual void msg_reply(rcvid msg_rcvid, int status, void* msg, int size) = 0;
    virtual void msg_reply_error(rcvid msg_rcvid, int error_code) = 0;
};

} /* namespace utils */

#endif /* SRC_DISPATCHER_IIPC_H_ */
