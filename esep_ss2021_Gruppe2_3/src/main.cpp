#include <dispatcher/Dispatcher.h>
#include <embedded_recorder/recorder.h>
#include <embedded_recorder/replayer.h>
#include <logic/clients/heartbeat_client.h>
#include <logic/clients/operation_manager_client.h>
#include <logic/clients/recieve_wrpc_client.h>
#include <logic/clients/height_measurement_client.h>
#include <logic/clients/metal_detection_client.h>
#include <logic/clients/sort_wrpc_client.h>
#include <logic/clients/wrpc_transfer_client.h>
#include <logic/clients/answer_transfer_req_client.h>
#include <logic/clients/error_listener_client.h>
#include <logic/clients/flip_handler_client.h>
#include <logic/clients/service_mode_client.h>
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
#include "logic/datamodel/unit_data.h"

//#define LOGGER_TRACE_DISPATCHED_EVENTS

#ifdef TEST_ENABLE
#include <gtest/gtest.h>
#endif

using namespace embedded_recorder;
using namespace logic;
using EventType = dispatcher::EventType;
using Event = dispatcher::Event;

void wait_for_exit();

std::shared_ptr<argument_parser::Arguments> args{nullptr};

using namespace dispatcher;
using client_ptr = std::unique_ptr<DispatcherClient>;

struct Clients {
    const std::unique_ptr<dispatcher::Dispatcher> dispatcher;
    std::vector<std::unique_ptr<DispatcherClient>> _clients{std::vector<client_ptr>()};

    Clients() : dispatcher(new dispatcher::Dispatcher(args->mode.str)) {
        _clients.push_back(client_ptr(new timer::AsyncTimerService(args->mode.str)));
        _clients.push_back(client_ptr(new hal::HalManagerAct(args->mode.str)));
        _clients.push_back(client_ptr(new clients::HeartbeatClient(args->mode.str)));

        if (!args->playback)
            _clients.push_back(client_ptr(new hal::HalManagerSen(args->mode.str)));

        if (!args->single)
            dispatcher->connect_to_other(args->mode.other_str);

        if (args->record)
            _clients.push_back(client_ptr(new Recorder(args->mode.str, args->filename)));
        if (args->playback) {
            _clients.push_back(client_ptr(new Replayer(args->mode.str, args->filename)));
        }
    }
};


int main(int argc, char **argv) {

#ifdef TEST_ENABLE
    if (argc > 1 && !strcmp(argv[1], "-t")) {
        Logger::setup("test logger", true, false);
        Logger::get()->set_level(spdlog::level::level_enum::debug);
        Logger::get()->set_pattern("[%n] %v");
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
    //DemoClient client(args->mode.str, "DEMO");

    auto data = std::make_shared<logic::datamodel::UnitData>(
                args->mode.secondary?
                        logic::datamodel::UnitType::SECONDARY : logic::datamodel::UnitType::PRIMARY
                        );
    logic::clients::OperationManagerClient op_mngr(args->mode.str, data.get());
    logic::clients::ReceiveWrpcClient rec_wrpc_client(args->mode.str, data.get());
    logic::clients::HeightMeasurementClient he_meas_client(args->mode.str, data.get());
    logic::clients::MetalDetectionClient metal_dtc_client(args->mode.str, data.get());
    logic::clients::SortWrpcClient sort_client(args->mode.str, data.get());
    logic::clients::WrpcTransferClient transfer_client(args->mode.str, data.get());
    logic::clients::AnswerTransferReqClient ans_transfer(args->mode.str, data.get());
    logic::clients::ErrorListenerClient error_listener(args->mode.str, data.get());
    logic::clients::FlipHandlerClient flip_handler(args->mode.str, data);
    logic::clients::ServiceModeClient service_mode(args->mode.str, data.get());

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

