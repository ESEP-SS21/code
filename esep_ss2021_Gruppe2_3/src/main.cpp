#include <argument_parser.hpp>
#include <dispatcher/Dispatcher.h>
#include <dispatcher/Event.h>
#include <embedded_recorder/recorder.h>
#include <embedded_recorder/replayer.h>
#include <hal/HalManagerAct.h>
#include <hal/HalManagerSen.h>
#include <logic/clients/height_measurement_client.h>
#include <logic/clients/metal_detection_client.h>
#include <logic/clients/operation_manager_client.h>
#include <logic/clients/recieve_wrpc_client.h>
#include <logic/clients/sort_wrpc_client.h>
#include <logic/clients/wrpc_transfer_client.h>
#include <logic/clients/heartbeat_client.h>
#include <logic/datamodel/unit_data.h>
#include <Logger.h>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/logger-inl.h>
#include <timer/AsyncTimerService.h>
#include <cstdio>
#include <cstring>
#include <memory>

#ifdef TEST_ENABLE
#include <gtest/gtest.h>

#endif

using namespace embedded_recorder;
using namespace logic;
using EventType = dispatcher::EventType;
using Event = dispatcher::Event;

void wait_for_exit();

std::shared_ptr<argument_parser::Arguments> args{nullptr};
using namespace logic::datamodel;
using namespace logic::clients;

UnitData * data;

struct Clients {
    const std::unique_ptr<dispatcher::Dispatcher> dispatcher;
    const std::unique_ptr<timer::AsyncTimerService> timer_svc;
    const std::unique_ptr<hal::HalManagerAct> hal_mngrAct;
    std::unique_ptr<hal::HalManagerSen> hal_mngrSen{nullptr};
    std::unique_ptr<embedded_recorder::Recorder> recorder{nullptr};
    std::unique_ptr<embedded_recorder::Replayer> replayer{nullptr};


    //STMS
    const std::unique_ptr<HeartbeatClient> hrtbt;
    const std::unique_ptr<OperationManagerClient> op_mngr;
    const std::unique_ptr<ReceiveWrpcClient> rec_wrpc;
    const std::unique_ptr<HeightMeasurementClient> he_meas;
    const std::unique_ptr<MetalDetectionClient> metal_dtc;
    const std::unique_ptr<SortWrpcClient> sort;
    const std::unique_ptr<WrpcTransferClient> transfer;

    Clients()
        : dispatcher(new dispatcher::Dispatcher(args->mode.str)),
          timer_svc(new timer::AsyncTimerService(args->mode.str)),
          hal_mngrAct(new hal::HalManagerAct(args->mode.str)),
          hrtbt(new HeartbeatClient(args->mode.str)),
          op_mngr(new OperationManagerClient(args->mode.str, data)),
          rec_wrpc(new ReceiveWrpcClient(args->mode.str, data)),
          he_meas(new HeightMeasurementClient(args->mode.str, data)),
          metal_dtc(new MetalDetectionClient(args->mode.str, data)),
          sort(new SortWrpcClient(args->mode.str, data)),
          transfer(new WrpcTransferClient(args->mode.str, data))
    {
        if (args->playback){
            replayer = std::unique_ptr<Replayer>(new Replayer(args->mode.str, args->filename));
            replayer->start();
        }
        else
            hal_mngrSen = std::unique_ptr<hal::HalManagerSen>(new hal::HalManagerSen(args->mode.str));

        if (args->record)
            recorder = std::unique_ptr<Recorder>(new Recorder(args->mode.str, args->filename));

        if (!args->single)
            dispatcher->connect_to_other(args->mode.other_str);
    }
};


int main(int argc, char **argv) {

#ifdef TEST_ENABLE
    if (argc > 1 && !strcmp(argv[1], "-t")) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
#endif

    args = argument_parser::parse(argc, argv);
    data = new UnitData(args->mode.secondary ? UnitType::PRIMARY : UnitType::SECONDARY);
    Logger::setup(args->mode.str, true, true);
    Logger::Logger _logger = Logger::get();
    _logger->info(">>>>>>>>> running in {} mode <<<<<<<<<", args->mode.str);
    if (args->verbose)
        _logger->set_level(spdlog::level::debug);
    else
        _logger->set_level(spdlog::level::info);

    Clients clients;
    //DemoClient client(args->mode.str, "DEMO");
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

