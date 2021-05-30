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
#include "hal/HalManager.h"
#include "timer/AsyncTimerService.h"

#ifdef TEST_ENABLE
#include <gtest/gtest.h>
#endif

void fail_and_exit();
void primary();
void secondary();

int main(int argc, char **argv) {

    enum class Mode {
        NONE, Primary, Secondary, Test, TestVerbouse
    };

    Mode mode = Mode::NONE;

    if (argc < 2)
        fail_and_exit();
    mode = strcmp(argv[1], "-p") == 0 ? Mode::Primary   :
           strcmp(argv[1], "-s") == 0 ? Mode::Secondary :
           strcmp(argv[1], "-t") == 0 ? Mode::Test      : Mode::NONE;

    bool quiet = false;
    if (argc > 2){
        quiet = strcmp(argv[2], "-q") == 0;
    }

    if (mode == Mode::NONE)
        fail_and_exit();
    std::string mode_str = mode == Mode::Primary   ? "PRI" :
                           mode == Mode::Secondary ? "SEC" :
                                   "TEST";


    Logger::setup(mode_str, true, "log/log.txt");
    Logger::Logger _logger = Logger::get();
    if (quiet)
        _logger->set_level(spdlog::level::off);
    else
        _logger->set_level(spdlog::level::trace);

    _logger->info(">>>>>>>>> running in {} mode <<<<<<<<<", mode_str);

#ifdef TEST_ENABLE
    if (mode == Mode::Test){
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
#else
    if (mode == Mode::Test){
        printf("Test are not compiled\n");
        fail_and_exit();
    }
#endif

    if (mode == Mode::Primary)
        primary();
    if (mode == Mode::Secondary)
        secondary();

    return 0;
}

void fail_and_exit() {
    printf("Usage %s -s | -c");
    exit(EXIT_FAILURE);
}

using EventType = dispatcher::EventType;
using Event = dispatcher::Event;

const std::string D_PRI = "PRI";
const std::string D_SEC = "SEC";

void primary() {
    dispatcher::Dispatcher disp(D_PRI);
    disp.connect_to_other(D_SEC);
    timer::AsyncTimerService timer_svc(D_PRI);
    hal::HalManager hal_mngr(D_PRI);
    DemoClient client(D_PRI, "DEMO");
    usleep(1000 * 1000 * 1000);
}

void secondary() {
    dispatcher::Dispatcher disp(D_SEC);
    disp.connect_to_other(D_PRI);
    hal::HalManager hal_mngr(D_SEC);
    usleep(1000 * 1000 * 1000);
}

