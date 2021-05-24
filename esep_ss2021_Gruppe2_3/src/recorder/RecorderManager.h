/*
 * RecorderManager.h
 *
 *  Created on: 24.05.2021
 *      Author: Lasse
 */

#ifndef SRC_RECORDER_RECORDERMANAGER_H_
#define SRC_RECORDER_RECORDERMANAGER_H_

#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "dispatcher/cnnMngmnt/QnxConnection.h"
#include "dispatcher/DispatcherClient.h"
#include "dispatcher/Event.h"
#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include <fstream>
#include "dispatcher/Event.h"
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>
#include "utils.h"



namespace recorder {

class RecorderManager: public dispatcher::DispatcherClient {
public:
    RecorderManager(const std::string& dispatcher_name, const std::string& input);
    void handle(dispatcher::Event& event);
    virtual ~RecorderManager();
private:
    std::thread _replay_thread;
    void playback_fnct(const std::string& input);
    std::ofstream _file;
    std::string _date;
    nlohmann::json _j;


};

} /* namespace replayer */

#endif /* SRC_RECORDER_RECORDERMANAGER_H_ */
