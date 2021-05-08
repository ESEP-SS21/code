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

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#ifdef TEST_ENABLE

#include <gtest/gtest.h>
#include "tests.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();

#else

    int main(int argc, char **argv) {

        //spdlog::set_default_logger(stdout_logger);
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
        //spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");
        my_logger->error("Hello {} {} !!", "param1", 123.4);
        spdlog::info("Hello, World!");

        dispatcher::dispatcher disp("dispatcher");

        DemoClient client("dispatcher");
        DemoClient client2("dispatcher");

        client.subscribe_evnt(dispatcher::EventType::Event12);
        client2.subscribe_evnt(dispatcher::EventType::Event12);

        client2.subscribe_evnt(dispatcher::EventType::AnotherEvent);

        client.send_evnt({dispatcher::EventType::Event12, 42}, 3);

        usleep(1000*1000*1);

        client.send_evnt({dispatcher::EventType::AnotherEvent, 33}, 3);

        usleep(1000*1000*2);
        return 0;
    }

#endif

