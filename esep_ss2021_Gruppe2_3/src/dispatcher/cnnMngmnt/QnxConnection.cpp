#include <dispatcher/cnnMngmnt/QnxConnection.h>
#include <errno.h>
#include <iostream>
#include <chrono>
#include <thread>

namespace dispatcher {
namespace cnnMngmnt {

// TODO call ConnectDetach() for correct resource deallocation

QnxConnection::QnxConnection(const std::string &name) {
    int retry_count = 0;
    std::cout<<"try to connect" << std::endl;
    while((_id = name_open(name.c_str(), NAME_FLAG_ATTACH_GLOBAL)) == -1){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if(retry_count>=100){
            std::cout << "connecting to channel " << name << " failed after " << retry_count << "attempts" << std::endl;
            break;
        }
        retry_count++;
    }
}

QnxConnection::QnxConnection(chid chid) {
    int retry_count = 0;
    while((_id = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0)) == -1){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if(retry_count>=100){
            std::cout << "connecting to channel " << chid << " failed after " << retry_count << " attempts" << std::endl;
            break;
        }
        retry_count++;
    }
}

QnxConnection::~QnxConnection(){
    ConnectDetach(_id);
}

status_code QnxConnection::msg_send(iov_t *iov, int iov_size) const {
    status_code s = MsgSendvs(_id, iov, iov_size, nullptr, 0);
    if (-1 == s)
        //An error occurred (errno is set), or the server called MsgError*() (errno is set to the error value passed to MsgError()).
        std::cout << "error while sending" << std::endl;
    return s;
}

void QnxConnection::msg_send_pulse(int priority, int code, int value) const {
    if (-1 == MsgSendPulse(_id, priority, code, value)) {
        std::cout << "error while sending puls" << std::endl;
        std::cout << "log(-1) failed: " << errno << '\n';
    }
}

}
}/* namespace dispatcher */
