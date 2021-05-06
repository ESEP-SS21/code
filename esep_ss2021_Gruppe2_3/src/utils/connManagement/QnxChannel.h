#ifndef SRC_UTILS_QNXIPCCHANNEL_H_
#define SRC_UTILS_QNXIPCCHANNEL_H_

#include <sys/dispatch.h>
#include <string>
#include <errno.h>

#include "IIpcChannel.h"

namespace connManagement {

class QnxChannel: public IIpcChannel {

public:
    QnxChannel() :
            _chid(ChannelCreate(0)) {
    }

    QnxChannel(const std::string &attach_string) {
        std::cout << attach_string << std::endl;
        name_attach_t* _attach = name_attach(nullptr, attach_string.c_str(),
                NAME_FLAG_ATTACH_GLOBAL);
        if (nullptr == _attach) {
            std::cout << "error while name_attach" << std::endl;
        }
        _chid = _attach->chid;
        std::cout << "chid of named server: " << _chid << std::endl;

    }

    virtual ~QnxChannel() override {
        std::cout << "descturctor called" << std::endl;
        if (_attach != nullptr)
            name_detach(_attach, 0);
    }

    rcvid msg_receive(void* msg, int size) override {
        rcvid r = MsgReceive(_chid, msg, size, nullptr); // TODO msg-info ins interface?
        if (r == -1) {
            std::cout << "log(-1) failed: " << std::strerror(errno) << '\n';
            std::cout << "error while receive" << std::endl;
        }
        return r;
    }

    void msg_reply(rcvid msg_rcvid, status_code status, void* msg, int size) override {
        if (-1 == MsgReply(msg_rcvid, status, msg, size))
            std::cout << "error while replying" << std::endl;
    }

    void msg_reply_error(rcvid msg_rcvid, int error_code) override {
        if (-1 == MsgError(msg_rcvid, error_code))
            std::cout << "error while replying with error" << std::endl;
    }

private:
    int _chid;
    /**
     * nullptr when channel is unnamed
     */
    name_attach_t* _attach { nullptr };

};

} /* namespace utils */

#endif /* SRC_UTILS_QNXIPCCHANNEL_H_ */
