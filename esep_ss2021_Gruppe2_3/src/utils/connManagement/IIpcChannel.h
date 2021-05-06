/*
 * IIpc.h
 *
 *  Created on: 05.05.2021
 *      Author: hugop
 */

#ifndef SRC_DISPATCHER_IIPC_H_
#define SRC_DISPATCHER_IIPC_H_

namespace connManagement {

using rcvid = int;
using conid = int;
using status_code = int;
using header_t = struct _pulse;

class IIpcChannel {
public:

    virtual ~IIpcChannel() = default;
    virtual void msg_send_pulse(conid reciever_id, int priority, int code, int value) = 0;
    virtual rcvid msg_receive(void* msg, int size) = 0;
    virtual void msg_reply(rcvid msg_rcvid, int status, void* msg, int size) = 0;
    virtual status_code msg_send(conid reciever_id, void* smsg, int smsg_size, void* rmsg,
            int rmsg_size) = 0;
    virtual void msg_reply_error(rcvid msg_rcvid, int error_code) = 0;
};

} /* namespace utils */

#endif /* SRC_DISPATCHER_IIPC_H_ */
