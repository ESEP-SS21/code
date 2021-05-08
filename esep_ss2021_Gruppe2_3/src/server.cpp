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
        for (int i = 0; i < 69; i++){
            _logger->error("---------------------------------- {} --------------------------------------",i);
        }
        
        int ret;
        printf("gns must be running.\n");
        if (argc < 2) {
            printf("Usage %s -s | -c \n", argv[0]);
            ret = EXIT_FAILURE;
        }
        else if (strcmp(argv[1], "-p") == 0) {
            dispatcher::dispatcher disp("dispatcherp");
            disp.connect_to_other("dispatchers");
            DemoClient client("dispatcherp");
            dispatcher::Event e ={dispatcher::EventType::Event12, true, 42};
            client.send_evnt(e, 3);
            usleep(1000*1000*10);
        }
        else if (strcmp(argv[1], "-s") == 0) {
            dispatcher::dispatcher disp("dispatchers");
            disp.connect_to_other("dispatcherp");
            DemoClient client("dispatchers");
            dispatcher::Event e = {dispatcher::EventType::Event12, true, 42};
            client.send_evnt(e, 3);
            usleep(1000*1000*10);

        }
        else {
            printf("Usage %s -s | -c \n", argv[0]);
            ret = EXIT_FAILURE;
        }
        return ret;
    }

    int test(){

        dispatcher::dispatcher disp("dispatcher_p");

        DemoClient client("dispatcher_p");
        DemoClient client2("dispatcher_p");

        using EventType = dispatcher::EventType;

        client.subscribe_evnt(EventType::Event12);
        client2.subscribe_evnt(EventType::Event12);
        client2.subscribe_evnt(EventType::AnotherEvent);

        client.send_evnt( {EventType::Event12, false ,42}, 3);

        usleep(1000*1000*1);

        client.send_evnt( {EventType::AnotherEvent, false, 33}, 3);

        usleep(1000*1000*2);
        return 0;
    }

#endif

