#pragma once

#include <string>
#include "../connection_management/namespacedata.h"
#include "Logger.h"

namespace dispatcher {
namespace connection_management {

/**
 * Used for sending messages to a QnxChannel.
 */
class QnxConnection {
public:
    QnxConnection(const std::string &receiver_attach_string);
    QnxConnection(connection_management::chid receiver_chid);
    virtual ~QnxConnection();
    int get_id();
    int msg_send_pulse(int priority, int code, int value) const;
    status_code msg_send(iov_t *iov, int iov_size) const;

private:
    Logger::Logger _logger { Logger::get() };
    int _id;
};

} /* namespace cnnMngmnt*/
} /* namespace dispatcher*/
