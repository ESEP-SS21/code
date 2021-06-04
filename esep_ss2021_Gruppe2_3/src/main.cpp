#include <dispatcher/Dispatcher.h>
#include <Logger.h>
#include <iostream>
#include "hal/gpiowrapper.h"
#include "hal/hal.h"
#include <thread>
#include <chrono>
#include "DemoClient.h"
#include "dispatcher/Event.h"
#include <sys/dispatch.h>
#include "dispatcher/cnnMngmnt/QnxChannel.h"
#include "hal/HalManagerAct.h"
#include "hal/HalManagerSen.h"
#include "timer/AsyncTimerService.h"
#include "argument_parser.hpp"
#include "logic/util/heartbeat_client.h"
#include <embedded_recorder/Recorder.h>
#include <embedded_recorder/Replayer.h>

#ifdef TEST_ENABLE
#include <gtest/gtest.h>

#endif

void primary();
void secondary();

bool record;
bool playback;
std::string filename;


int main(int argc, char **argv) {

#ifdef TEST_ENABLE
    if (argc > 1 && !strcmp(argv[1], "-t")) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

#endif

    auto args = argument_parser::parse(argc, argv);
    record = args->record;
    playback = args->playback;
    filename = args->filename;
    std::string mode_str = args->secondary ? "SEC" : "PRI";
    Logger::setup(mode_str, true, "log/log.txt");
    Logger::Logger _logger = Logger::get();
    _logger->info(">>>>>>>>> running in {} mode <<<<<<<<<", mode_str);
    if (args->verbose)
        _logger->set_level(spdlog::level::debug);
    else
        _logger->set_level(spdlog::level::warn);


    if (args->secondary)
        secondary();
    else
        primary();


    return 0;
}

using EventType = dispatcher::EventType;
using Event = dispatcher::Event;

const std::string D_PRI = "PRI";
const std::string D_SEC = "SEC";

void wait_for_exit() {
    while (true) {
        char c = getchar();
        if (c == 'q') {
            Logger::get()->set_level(spdlog::level::debug);
            Logger::get()->info(">>>>>>>>> EXIT <<<<<<<<<");
            return;
        }
    }
}

void primary() {
    dispatcher::Dispatcher disp(D_PRI);
    //disp.connect_to_other(D_SEC);
    timer::AsyncTimerService timer_svc(D_PRI);
    logic::util::HeartbeatClient hrtbt(D_PRI);
    DemoClient client(D_PRI, "DEMO");

    if(record){
        hal::HalManagerAct hal_mngrAct(D_PRI);
        hal::HalManagerSen hal_mngrSen(D_PRI);
        embedded_recorder::Recorder recorder(D_PRI);

        wait_for_exit();
    }
    else if(playback){
        hal::HalManagerAct hal_mngrAct(D_PRI);
        embedded_recorder::Replayer replayer(D_PRI, filename);
        replayer.start();
        wait_for_exit();
    }else{
        hal::HalManagerAct hal_mngrAct(D_PRI);
        hal::HalManagerSen hal_mngrSen(D_PRI);
        wait_for_exit();
    }

}

void secondary() {
    dispatcher::Dispatcher disp(D_SEC);
    disp.connect_to_other(D_PRI);
    //hal::HalManager hal_mngr(D_SEC);
    if(record){
            hal::HalManagerAct hal_mngrAct(D_PRI);
            hal::HalManagerSen hal_mngrSen(D_PRI);
            embedded_recorder::Recorder recorder(D_PRI);

            wait_for_exit();
        }
        else if(playback){
            hal::HalManagerAct hal_mngrAct(D_PRI);
            embedded_recorder::Replayer replayer(D_PRI, filename);
            replayer.start();
            wait_for_exit();
        }else{
            hal::HalManagerAct hal_mngrAct(D_PRI);
            hal::HalManagerSen hal_mngrSen(D_PRI);
            wait_for_exit();
        }
}

