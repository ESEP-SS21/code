#include "QnxChannel.h"
#include <sys/dispatch.h>
#include <errno.h>
#include <iostream>

namespace dispatcher {
namespace cnnMngmnt {

QnxChannel::QnxChannel() :
        _id(ChannelCreate(0)) {
}

QnxChannel::QnxChannel(const std::string &attach_string) {
    name_attach_t* _attach = name_attach(nullptr, attach_string.c_str(),
    NAME_FLAG_ATTACH_GLOBAL);
    if (nullptr == _attach) {
        _logger->error("while attaching channel '{}'", attach_string);
        throw;
    }
    _id = _attach->chid;
    _logger->trace("Attached named channel '{}' with chid {}", attach_string, _id);

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

void QnxChannel::msg_reply(status_code status) const {
    if (-1 == _last_message_id)
        _logger->error("Trying to reply to a msg, but there is no msg to reply to");
    if (-1 == MsgReply(_last_message_id, status, nullptr, 0))
        _logger->error("while replying");
}

void QnxChannel::msg_reply_error(int error_code) const {
    if (-1 == _last_message_id)
        _logger->error("Trying to reply to a msg, but there is no msg to reply to");
    if (-1 == MsgError(_last_message_id, error_code))
        _logger->error("while replying with error '{}'", error_code);
}

void QnxChannel::msg_read(void *msg, _Sizet size, _Sizet offset) const {
    MsgRead(_last_message_id, msg, size, offset);
}

}
} /* namespace utils */

