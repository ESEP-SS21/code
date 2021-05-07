#ifndef SRC_DISPATCHER_IIPC_H_
#define SRC_DISPATCHER_IIPC_H_

#include "namespacedata"

namespace connManagement {

enum class MsgType { puls, sync, qnx, error };

class IIpcChannel {
public:
    virtual ~IIpcChannel() = default;
    virtual MsgType msg_receive(void* msg, int size) = 0;
    virtual void msg_reply(int status, void* msg, int size) = 0;
    virtual void msg_reply_error(int error_code) = 0;
    virtual chid get_chid() = 0;
    virtual void msg_read(void *msg, _Sizet size, _Sizet offset) = 0;

private:
    chid _id;
    rcvid _last_message_id {-1};

};
} /* namespace utils */

#endif /* SRC_DISPATCHER_IIPC_H_ */
