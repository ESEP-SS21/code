#pragma once

#include "namespacedata"
#include <string>

namespace dispatcher {
namespace cnnMngmnt {

enum class MsgType {
    puls, sync, error
};

class QnxChannel {
public:
    virtual ~QnxChannel();
    QnxChannel();
    QnxChannel(const std::string &attach_string);

    MsgType msg_receive(void* msg, int size);
    void msg_reply(int status, void* msg, int size);
    void msg_reply_error(int error_code);
    void msg_read(void *msg, _Sizet size, _Sizet offset);
    chid get_chid() {
        return _id;
    }

private:
    chid _id;
    rcvid _last_message_id { -1 };
    /**
     * nullptr when channel is unnamed
     */
    name_attach_t* _attach { nullptr };

};
}
} /* namespace utils */
