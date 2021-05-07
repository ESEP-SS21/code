#ifndef SRC_UTILS_QNXIPCCHANNEL_H_
#define SRC_UTILS_QNXIPCCHANNEL_H_

#include <sys/dispatch.h>
#include <string>
#include <errno.h>
#include <iostream>

#include "IIpcChannel.h"

namespace connManagement {

class QnxChannel: public IIpcChannel {

public:
    QnxChannel() :
            _id(ChannelCreate(0)) {
    }

    QnxChannel(const std::string &attach_string) {
        std::cout << attach_string << std::endl;
        name_attach_t* _attach = name_attach(nullptr, attach_string.c_str(),
                NAME_FLAG_ATTACH_GLOBAL);
        if (nullptr == _attach) {
            std::cout << "error while name_attach" << std::endl;
        }
        _id = _attach->chid;
        std::cout << "chid of named server: " << _id << std::endl;
    }

    virtual ~QnxChannel() override {
        if (_attach != nullptr)
            name_detach(_attach, 0);
    }

    MsgType msg_receive(void* msg, int size) override {
        _last_message_id = MsgReceive(_id, msg, size, nullptr);
        switch (_last_message_id){
        case -1:
            return MsgType::error;
        case 0:
            return MsgType::puls;
        default:
            return MsgType::sync;
        }
    }

    void msg_reply(status_code status, void* msg, int size) override {
        if (-1 == _last_message_id)
            std::cout << "no msg to reply to" << std::endl;
        if (-1 == MsgReply(_last_message_id, status, msg, size))
            std::cout << "error while replying" << std::endl;
    }

    void msg_reply_error(int error_code) override {
        if (-1 == _last_message_id)
            std::cout << "no msg to reply to" << std::endl;
        if (-1 == MsgError(_last_message_id, error_code))
            std::cout << "error while replying with error" << std::endl;
    }

    void msg_read(void *msg, _Sizet size, _Sizet offset){
        MsgRead(_last_message_id, msg, size, offset);
    }


    chid get_chid() override {
        return _id;
    }

private:
    chid _id;
    rcvid _last_message_id {-1};
    /**
     * nullptr when channel is unnamed
     */
    name_attach_t* _attach { nullptr };

};

} /* namespace utils */

#endif /* SRC_UTILS_QNXIPCCHANNEL_H_ */
