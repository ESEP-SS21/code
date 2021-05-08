#include <Logger.h>
#include <iostream>
#include "simqnxgpioapi.h" // must be last include !!!
#include "hal/gpiowrapper.h"
#include "hal/hal.h"
#include "hal/actuators/cb_motor.h"
#include <thread>
#include <chrono>
#include "dispatcher/dispatcher.h"
#include "DemoClient.h"
#include "dispatcher/Event.h"

#include <sys/dispatch.h>
#include "dispatcher/cnnMngmnt/QnxChannel.h"

#ifdef TEST_ENABLE

#include <gtest/gtest.h>
#include "tests.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();

#else

    void fail_and_exit();
    void primary();
    void secondary();

    int main(int argc, char **argv) {



        enum class Mode {NONE, Primary, Secondary};

        Mode mode = Mode::NONE;

        if (argc < 2)
            fail_and_exit();
        mode = strcmp(argv[1], "-p") == 0 ? Mode::Primary :
               strcmp(argv[1], "-s") == 0 ? Mode::Secondary: Mode::NONE;
        if (mode == Mode::NONE)
            fail_and_exit();

        Logger::setup(mode == Mode::Primary ? "PRI" : "SEC", true, "log/log.txt");
        Logger::Logger _logger = Logger::get();
        for (int i = 0; i < 69; i++) {
            _logger->error("---------------- {} ----------------",i);
        }

        if (mode == Mode::Primary)
            primary();
        if (mode == Mode::Secondary)
            secondary();

        return 0;
    }

    void fail_and_exit(){
        printf("Usage %s -s | -c");
        exit(EXIT_FAILURE);
    }

    void primary(){
        dispatcher::dispatcher disp("dispatcherp");
        disp.connect_to_other("dispatchers");
        DemoClient client("dispatcherp");
        client.subscribe_evnt(dispatcher::EventType::Event12);
        dispatcher::Event e = {dispatcher::EventType::Event12, true, 23};
        client.send_evnt(e, 3);
        usleep(1000*100);
        client.send_evnt(e, 3);
        usleep(1000*100);
        client.send_evnt(e, 3);
        usleep(1000*100);
        client.send_evnt(e, 3);
        usleep(1000*100);
    }

    void secondary(){
        dispatcher::dispatcher disp("dispatchers");
        disp.connect_to_other("dispatcherp");
        DemoClient client("dispatchers");
        client.subscribe_evnt(dispatcher::EventType::Event12);
        dispatcher::Event e = {dispatcher::EventType::Event12, true, 42};
        client.send_evnt(e, 3);
        usleep(1000*100);
        client.send_evnt(e, 3);
        usleep(1000*100);
        client.send_evnt(e, 3);
        usleep(1000*100);
        client.send_evnt(e, 3);
        usleep(1000*100);
    }

#endif

