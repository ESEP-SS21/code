#include <iostream>
#include "simqnxgpioapi.h" // must be last include !!!
#include "gpiowrapper.h"
#include "hal.h"
#include "actuators/cb_motor.h"
#include <thread>
#include <chrono>
#include "dispatcher/dispatcher.h"

#include <sys/dispatch.h>

#include "utils/connManagement/QnxChannel.h"

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
        my_logger->error("Hello {} {} !!", "param1", 123.4);

        std::cout << "test" << std::endl;
        usleep(1000*1000*3);
        std::cout << "test" << std::endl;

        //spdlog::info("Hello, World!");

        //spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");

        //std::unique_ptr<connManagement::QnxChannel>  channel (new connManagement::QnxChannel("test"));
        //dispatcher::dispatcher disp(std::move(channel));

//	connManagement::QnxConnection conn("test");
//	conn.msg_send_pulse(2, 53, 12345);
//
//	usleep(100000000);
//	hal::HAL::get_instance().get_stoplight().get()->blink(hal::GREEN,
//			hal::FAST);
//	std::this_thread::sleep_for (std::chrono::seconds(5));
//	hal::HAL::get_instance().get_stoplight().get()->enable(hal::YELLOW);
//	std::this_thread::sleep_for (std::chrono::seconds(2));
//	hal::HAL::get_instance().get_stoplight().get()->blink(hal::RED, hal::SLOW);
//	std::this_thread::sleep_for (std::chrono::milliseconds(4500));
//	hal::HAL::get_instance().get_stoplight().get()->enable(hal::GREEN);
//	std::this_thread::sleep_for (std::chrono::seconds(2));
//
//
//
        /*
         while (1) {
         //CBMotor
         hal::HAL::get_instance().get_cb_motor().get()->set_direction(hal::FAST_FORWARDS);
         usleep(1000 * 500);

         hal::HAL::get_instance().get_cb_motor().get()->set_direction(hal::FAST_BACKWARDS);
         usleep(1000 * 500);

         hal::HAL::get_instance().get_cb_motor().get()->set_direction(hal::SLOW_BACKWARDS);
         usleep(1000 * 500);

         hal::HAL::get_instance().get_cb_motor().get()->set_direction(hal::SLOW_FORWARDS);
         usleep(1000 * 500);

         hal::HAL::get_instance().get_cb_motor().get()->set_direction(hal::STOP);
         usleep(1000 * 500);

         //SortingMechanism
         hal::HAL::get_instance().get_sorting_mechanism().get()->open();
         usleep(1000 * 500);

         std::cout << hal::HAL::get_instance().get_sorting_mechanism().get()->is_open() << std::endl;
         usleep(1000 * 500);

         hal::HAL::get_instance().get_sorting_mechanism().get()->close();
         usleep(1000 * 500);

         std::cout << hal::HAL::get_instance().get_sorting_mechanism().get()->is_open() << std::endl;
         usleep(1000 * 500);
         }

         return 0;
         */
    }

#endif

