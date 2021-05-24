#include <dispatcher/Dispatcher.h>
#include <Logger.h>
#include <recorder_replayer/Recorder.h>
#include <recorder_replayer/Replayer.h>
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

        Logger::setup(mode_str, spdlog::level::trace, spdlog::level::err);
        Logger::Logger _logger = Logger::get();

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

    void primary(){
        dispatcher::Dispatcher disp("dispatcherp");
        //disp.connect_to_other("dispatchers");
        DemoClient client("dispatcherp", "DemoClient");

        recorder_replayer::Recorder recorder("dispatcherp");
        recorder_replayer::Replayer replayer("dispatcherp", "records/2021-05-24-15-30.json");

//        client.subscribe_evnt(dispatcher::EventType::Event12);
//        dispatcher::Event e = {dispatcher::EventType::AnotherEvent, true, 23};
//        client.send_evnt(e, 3);
//        usleep(1000*100);
//        client.send_evnt(e, 3);
//        usleep(1000*100);
//        client.send_evnt(e, 3);
//        usleep(1000*100);
//        client.send_evnt(e, 3);
          usleep(1000*1000);
    }

    void secondary(){
        dispatcher::Dispatcher disp("dispatchers");
        disp.connect_to_other("dispatcherp");
        DemoClient client("dispatchers", "DemoClient");
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

