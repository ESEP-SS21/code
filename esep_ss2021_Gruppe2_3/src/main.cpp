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

const std::shared_ptr<Arguments> args;

struct Clients {
    const std::unique_ptr<dispatcher::Dispatcher> dispatcher;
    const std::unique_ptr<timer::AsyncTimerService> timer_svc;
    const std::unique_ptr<hal::HalManagerAct> hal_mngrAct;
    const std::unique_ptr<hal::HalManagerSen> hal_mngrSen{nullptr};
    const std::unique_ptr<embedded_recorder::Recorder> recorder{nullptr};
    const std::unique_ptr<embedded_recorder::Replayer> replayer{nullptr};

    //STMS
    const std::unique_ptr<logic::util::HeartbeatClient> hrtbt;

    Clients(const std::string &dispatcher_name, const std::string &other_name, bool replay, bool record,
            const std::string &filename)
        : dispatcher(new dispatcher::Dispatcher(dispatcher_name)),
          timer_svc(new timer::AsyncTimerService(dispatcher_name)),
          hal_mngrAct(new hal::HalManagerAct(dispatcher_name)),
          hrtbt(new util::HeartbeatClient(dispatcher_name)) {

        if (replay)
            replayer = std::unique_ptr<Replayer>(new Replayer(dispatcher_name, filename));
        else
            hal_mngrSen = std::unique_ptr<hal::HalManagerSen>(new hal::HalManagerSen(dispatcher_name);

        if (record)
            recorder = std::unique_ptr<Recorder>(new Recorder(dispatcher_name));

        dispatcher->connect_to_other(other_name);
    }
}


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


    Clients clients(args->mode.str, args->mode.other_str, args->replay, args->playback, args->filename);
    DemoClient client(args->mode.str, "DEMO");
    wait_for_exit();
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

