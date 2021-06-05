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

using namespace embedded_recorder;
using namespace logic;
using EventType = dispatcher::EventType;
using Event = dispatcher::Event;

void wait_for_exit();

std::shared_ptr<argument_parser::Arguments> args{nullptr};

struct Clients {
    const std::unique_ptr<dispatcher::Dispatcher> dispatcher;
    const std::unique_ptr<timer::AsyncTimerService> timer_svc;
    const std::unique_ptr<hal::HalManagerAct> hal_mngrAct;
    std::unique_ptr<hal::HalManagerSen> hal_mngrSen{nullptr};
    std::unique_ptr<embedded_recorder::Recorder> recorder{nullptr};
    std::unique_ptr<embedded_recorder::Replayer> replayer{nullptr};

    //STMS
    const std::unique_ptr<logic::util::HeartbeatClient> hrtbt;

    Clients()
        : dispatcher(new dispatcher::Dispatcher(args->mode.str)),
          timer_svc(new timer::AsyncTimerService(args->mode.str)),
          hal_mngrAct(new hal::HalManagerAct(args->mode.str)),
          hrtbt(new util::HeartbeatClient(args->mode.str)) {

        if (args->playback){
            replayer = std::unique_ptr<Replayer>(new Replayer(args->mode.str, args->filename));
            replayer->start();
        }
        else
            hal_mngrSen = std::unique_ptr<hal::HalManagerSen>(new hal::HalManagerSen(args->mode.str));

        if (args->record)
            recorder = std::unique_ptr<Recorder>(new Recorder(args->mode.str));

        if (!args->single)
            dispatcher->connect_to_other(args->mode.other_str);
    }
};


int main(int argc, char **argv) {

#ifdef TEST_ENABLE
    if (argc > 1 && !strcmp(argv[1], "-t")) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
#endif

    args = argument_parser::parse(argc, argv);

    Logger::setup(args->mode.str, true, true);
    Logger::Logger _logger = Logger::get();
    _logger->info(">>>>>>>>> running in {} mode <<<<<<<<<", args->mode.str);
    if (args->verbose)
        _logger->set_level(spdlog::level::debug);
    else
        _logger->set_level(spdlog::level::info);

    Clients clients;
    DemoClient client(args->mode.str, "DEMO");
    wait_for_exit();

    return 0;
}


void wait_for_exit() {
    while (true) {
        char c = getchar();
        if (c == 'q') {
            Logger::get()->info(">>>>>>>>> EXIT <<<<<<<<<");
            return;
        }
    }
}

