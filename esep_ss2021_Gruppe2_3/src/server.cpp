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

    int main(int argc, char **argv) {

        Logger::setup("FTS1", true, "log/log.txt");

        Logger::Logger _logger = Logger::get();

        for (int i = 0; i < 999; i++){
            logger->error("---------------------------------- {} --------------------------------------",i);
        }

        dispatcher::dispatcher disp("dispatcher_p");

        DemoClient client("dispatcher_p");
        DemoClient client2("dispatcher_p");

        using EventType = dispatcher::EventType;

        client.subscribe_evnt(EventType::Event12);
        client2.subscribe_evnt(EventType::Event12);
        client2.subscribe_evnt(EventType::AnotherEvent);

        client.send_evnt( {EventType::Event12, 42}, 3);

        usleep(1000*1000*1);

        client.send_evnt( {EventType::AnotherEvent, 33}, 3);

        usleep(1000*1000*2);
        return 0;
    }

#endif

