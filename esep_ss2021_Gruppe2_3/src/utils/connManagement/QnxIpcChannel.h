/*
 * QnxIpc.h
 *
 *  Created on: 05.05.2021
 *      Author: hugop
 */

#ifndef SRC_UTILS_QNXIPCCHANNEL_H_
#define SRC_UTILS_QNXIPCCHANNEL_H_

#include <sys/dispatch.h>
#include <string>

#include "../connManagement/IIpcChannel.h"
#include "../connManagement/QnxConnection.h"
#include <errno.h>

namespace connManagement {

class QnxIpcChannel: public IIpcChannel {

public:
    QnxIpcChannel() :
            _chid(ChannelCreate(0)) {
    }

    QnxIpcChannel(const string &attach_string) {
        std::cout << attach_string << std::endl;
        name_attach_t* _attach = name_attach(nullptr, attach_string.c_str(), NAME_FLAG_ATTACH_GLOBAL);
        if (nullptr == _attach) {
            std::cout << "error while name_attach" << std::endl;
        }
        _chid = _attach->chid;
        std::cout << "chid of named server: " <<_chid << std::endl;

    }

//    static QnxIpcChannel CreateUnnamedChannel() {  //variante 2
    //    return QnxIpcChannel();
        //int conid = name_open(attach_string.c_str(),0);
        // int conidZuMirSelbst = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
        // senden an dispatcher mithilfe con conid

        // TODO private ctor der conid / chid / name_attach_t nimmt
        // oder Basisklasse extrahieren
    //}

    virtual ~QnxIpcChannel() override {
        std::cout << "descturctor called" << std::endl;
        if (_attach != nullptr)
            name_detach(_attach, 0);
    }

    rcvid msg_receive(void* msg, int size) override {
        rcvid r = MsgReceive(_chid, msg, size, nullptr); // TODO msg-info ins interface?
        if (r == -1){
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

     status_code msg_send(conid reciever_id, void* smsg, int smsg_size, void* rmsg,
            int rmsg_size) override {
        status_code s = MsgSend(reciever_id, smsg, smsg_size, rmsg, rmsg_size);
        if (-1 == s)
            //An error occurred (errno is set), or the server called MsgError*() (errno is set to the error value passed to MsgError()).
            std::cout << "error while sending" << std::endl;
        return s;
    }

     void msg_send_pulse(conid reciever_id, int priority, int code, int value) override {
        if (-1 == MsgSendPulse(reciever_id, priority, code, value)){
            std::cout << "error while sending puls" << std::endl;
            std::cout << "log(-1) failed: " << errno << '\n';
        }
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
