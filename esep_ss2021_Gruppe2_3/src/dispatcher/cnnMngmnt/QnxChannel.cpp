#include <sys/dispatch.h>
#include <errno.h>
#include "QnxChannel.h"
#include <iostream>

namespace dispatcher {
namespace cnnMngmnt {

QnxChannel::QnxChannel() :
        _id(ChannelCreate(0)) {
}

QnxChannel::QnxChannel(const std::string &attach_string) {
    std::cout << attach_string << std::endl;
    name_attach_t* _attach = name_attach(nullptr, attach_string.c_str(),
    NAME_FLAG_ATTACH_GLOBAL);
    if (nullptr == _attach) {
        std::cout << "error while name_attach" << std::endl;
    }
    _id = _attach->chid;
    std::cout << "chid of named server: " << _id << std::endl;
}

QnxChannel::~QnxChannel() {
    if (_attach != nullptr)
        name_detach(_attach, 0);
}

MsgType QnxChannel::msg_receive(void* msg, int size) {
    _last_message_id = MsgReceive(_id, msg, size, nullptr);
    switch (_last_message_id) {
    case -1:
        return MsgType::error;
    case 0:
        return MsgType::puls;
    default:
        return MsgType::sync;
    }
}

void QnxChannel::msg_reply(status_code status, void* msg, int size) const {
    if (-1 == _last_message_id)
        std::cout << "no msg to reply to" << std::endl;
    if (-1 == MsgReply(_last_message_id, status, msg, size))
        std::cout << "error while replying" << std::endl;
}

void QnxChannel::msg_reply_error(int error_code) const {
    if (-1 == _last_message_id)
        std::cout << "no msg to reply to" << std::endl;
    if (-1 == MsgError(_last_message_id, error_code))
        std::cout << "error while replying with error" << std::endl;
}

void QnxChannel::msg_read(void *msg, _Sizet size, _Sizet offset) const {
    MsgRead(_last_message_id, msg, size, offset);
}

}
} /* namespace utils */

