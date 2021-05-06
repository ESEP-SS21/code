/*
 * QnxConnection.h
 *
 *  Created on: 05.05.2021
 *      Author: hugop
 */

#ifndef SRC_UTILS_QNXCONNECTION_H_
#define SRC_UTILS_QNXCONNECTION_H_

namespace connManagement {

struct QnxConnection {
public:
    virtual ~QnxConnection();
    QnxConnection(string &name) {
        _id = name_open(name.c_str(), 0);
        if (-1 == _id)
            std::cout << "error while connecting to channel via name" << std::endl;
    }

    QnxConnection(connManagement::conid chid) {
        _id = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
        if (-1 == _id)
            std::cout << "error while connecting to channel via chid" << std::endl;
    }

    operator connManagement::conid() const {
        return _id;
    }

private:
    int _id;
};

} /* namespace dispatcher */

#endif /* SRC_UTILS_QNXCONNECTION_H_ */
