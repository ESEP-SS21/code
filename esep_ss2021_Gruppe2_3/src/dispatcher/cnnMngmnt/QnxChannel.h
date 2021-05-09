#pragma once

#include "namespacedata"
#include <string>
#include "Logger.h"

namespace dispatcher {
namespace cnnMngmnt {

enum class MsgType {
    puls, sync, error
};

class QnxChannel {
public:
    QnxChannel();
    QnxChannel(const std::string &attach_string);
    virtual ~QnxChannel();

    void msg_reply(status_code status) const;
    void msg_reply_error(int error_code) const;
    void msg_read(void *msg, _Sizet size, _Sizet offset) const;
    chid get_chid() const {
        return _id;
    }
    MsgType msg_receive(void* msg, int size);

private:
    Logger::Logger _logger { Logger::get() };
    chid _id;
    rcvid _last_message_id { -1 };
    /**
     * nullptr when channel is unnamed
     */
    name_attach_t* _attach { nullptr };

};
}
} /* namespace utils */
