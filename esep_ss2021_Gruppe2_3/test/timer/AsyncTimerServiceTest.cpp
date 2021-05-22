#include "tests.h"
#include "../src/dispatcher/dispatcher.h"
#include "../src/timer/ASyncTimerService.h"
#include "../src/dispatcher/cnnMngmnt/QnxChannel.h"
#include "../src/dispatcher/cnnMngmnt/QnxConnection.h"
#include "../src/dispatcher/Event.h"
#include "TestClient.h"
#include <chrono>
#include <string>

constexpr int timerToleranceMs = 10;
const std::string dispatcherPrefix = "TEST_DISP";
const std::string clienetPrefix = "TEST_CLIENT";

std::string getUniqueDispatcherName(std::string name) {
    static int i = 0;
    return fmt::format("{}_{}_{}", dispatcherPrefix, i++, name);
}

void testSingleTimerEventCode(int ms_time, int payload) {
    const std::string DISPATCHER_NAME = getUniqueDispatcherName(__FUNCTION__);
    dispatcher::Dispatcher disp(DISPATCHER_NAME);
    timer::AsyncTimerService timer_svc(DISPATCHER_NAME);
    TestClient client(DISPATCHER_NAME, fmt::format("{}_{}", clienetPrefix, __FUNCTION__));
    client.subscribe(dispatcher::EventType::EVNT_TIM_ALRT);

    dispatcher::Event e1 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(payload, ms_time), false };

    int msg_pio = 20;
    client.send(e1, msg_pio);
    dispatcher::Event rcv = client.recieve_event();
    ASSERT_EQ(rcv.payload, payload);
}

TEST(Timer, ReturnedEventCouldShouldEqualEventCodeWhichHasBeenSetUp) {
    testSingleTimerEventCode(10, 44);
    testSingleTimerEventCode(10, 45);
    testSingleTimerEventCode(10, 44);
}

TEST(Timer, TimePeriod) {
    const std::string DISPATCHER_NAME = "TEST_DISP_TIMER_PERIOD";
    dispatcher::Dispatcher disp(DISPATCHER_NAME);
    timer::AsyncTimerService timer_svc(DISPATCHER_NAME);
    TestClient client(DISPATCHER_NAME, "TEST_CLIENT_TIMER_PERIOD");
    client.subscribe(dispatcher::EventType::EVNT_TIM_ALRT);

    // short time period
    int expectedTime = 100;
    dispatcher::Event e1 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(42, expectedTime), false };

    auto time_start = std::chrono::high_resolution_clock::now();
    client.send(e1, 20);
    client.recieve_event();
    auto time_end = std::chrono::high_resolution_clock::now();
    auto delta =
            std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();

    ASSERT_TRUE(delta < expectedTime + timerToleranceMs && delta >= expectedTime);

    // long time period
    expectedTime = 1500;
    dispatcher::Event e2 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(42, expectedTime), false };

    time_start = std::chrono::high_resolution_clock::now();
    client.send(e2, 20);
    client.recieve_event();
    time_end = std::chrono::high_resolution_clock::now();

    delta = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
    ASSERT_TRUE(delta < expectedTime + timerToleranceMs && delta >= expectedTime);
}

TEST(Timer, MultipleTimers) {
    const std::string DISPATCHER_NAME = "TEST_DISP_TIMER_MULTIPLE";
    dispatcher::Dispatcher disp(DISPATCHER_NAME);
    timer::AsyncTimerService timer_svc(DISPATCHER_NAME);
    TestClient client(DISPATCHER_NAME, "TEST_CLIENT_TIMER_MULTIPLE");
    client.subscribe(dispatcher::EventType::EVNT_TIM_ALRT);

    int payload1 = 42;
    int payload2 = 23;
    int expectedTimeShort = 100;
    int expectedTimeLong = 200;

    dispatcher::Event e1 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(payload1, expectedTimeShort), false };
    dispatcher::Event e2 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(payload2, expectedTimeLong), false };

    auto time_start = std::chrono::high_resolution_clock::now();
    client.send(e1, 20);
    client.send(e2, 20);

    dispatcher::Event rcv1 = client.recieve_event();
    auto time_end = std::chrono::high_resolution_clock::now();
    ASSERT_EQ(rcv1.payload, payload1);
    auto delta =
            std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
    ASSERT_TRUE(delta < expectedTimeShort + timerToleranceMs && delta >= expectedTimeShort);

    dispatcher::Event rcv2 = client.recieve_event();
    time_end = std::chrono::high_resolution_clock::now();
    ASSERT_EQ(rcv2.payload, payload2);
    delta = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
    ASSERT_TRUE(delta < expectedTimeLong + timerToleranceMs && delta >= expectedTimeLong);
}
