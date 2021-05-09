#include <dispatcher/Dispatcher.h>
#include <Logger.h>
#include <iostream>
#include "simqnxgpioapi.h" // must be last include !!!
#include "hal/gpiowrapper.h"
#include "hal/hal.h"
#include "hal/actuators/cb_motor.h"
#include <thread>
#include <chrono>
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
        std::string mode_str = mode == Mode::Primary ? "PRI" : "SEC";

        Logger::setup(mode_str, true, "log/log.txt");
        Logger::Logger _logger = Logger::get();
        _logger->set_level(spdlog::level::trace);

        _logger->info(">>>>>>>>> running in {} mode <<<<<<<<<", mode_str);

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

    using EventType = dispatcher::EventType;
    using Event = dispatcher::Event;

    void primary(){
        dispatcher::Dispatcher disp("dispatcherp");
        disp.connect_to_other("dispatchers");
        DemoClient client("dispatcherp", "DemoClient");

        client.subscribe({EventType::Event12, EventType::SomeEvent});
        Event e = {EventType::Event12, true, 23};

        client.send(e, 3);
        usleep(1000*100);
        client.send(e, 3);
        usleep(1000*100);
        client.send(e, 3);
        usleep(1000*100);
        client.send(e, 3);
        usleep(1000*100);
    }

    void secondary(){
        dispatcher::Dispatcher disp("dispatchers");
        disp.connect_to_other("dispatcherp");
        DemoClient client("dispatchers", "DemoClient");

        client.subscribe(EventType::Event12);

        Event e = {EventType::Event12, true, 42};
        Event e1 = {EventType::SomeEvent, true, 13};
        Event e2 = {EventType::AnotherEvent, true, 5};

        client.send(e, 3);
        usleep(1000*100);
        client.send(e1, 3);
        usleep(1000*100);
        client.send(e2, 3);
        usleep(1000*100);
    }

#endif

