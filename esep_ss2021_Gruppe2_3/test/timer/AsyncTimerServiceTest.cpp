#include "tests.h"
#include "../src/dispatcher/dispatcher.h"
#include "../src/timer/ASyncTimerService.h"
#include "../src/dispatcher/cnnMngmnt/QnxChannel.h"
#include "../src/dispatcher/cnnMngmnt/QnxConnection.h"
#include "../src/dispatcher/Event.h"
#include "TestClient.h"
#include <chrono>

TEST(Timer, ReturnedEventNumber) {
    dispatcher::Dispatcher disp("TEST_DISP_TIMER_NUMBER");
    timer::AsyncTimerService timer_svc("TEST_DISP_TIMER_NUMBER");
    TestClient client("TEST_DISP_TIMER_NUMBER", "TEST_CLIENT_TIMER_PERIOD");
    client.subscribe(dispatcher::EventType::EVNT_TIM_ALRT);

    dispatcher::Event e1 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(42, 10), false };
    client.send(e1, 20);
    dispatcher::Event rcv1 = client.recieve_event();
    int payload1 = rcv1.payload;
    ASSERT_EQ(payload1, 42);

    dispatcher::Event e2 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(23, 10), false };
    client.send(e2, 20);
    dispatcher::Event rcv2 = client.recieve_event();
    int payload2 = rcv2.payload;
    ASSERT_EQ(payload2, 23);
}

TEST(Timer, TimePeriod) {
    dispatcher::Dispatcher disp("TEST_DISP_TIMER_PERIOD");
    timer::AsyncTimerService timer_svc("TEST_DISP_TIMER_PERIOD");
    TestClient client("TEST_DISP_TIMER_PERIOD", "TEST_CLIENT_TIMER_PERIOD");
    client.subscribe(dispatcher::EventType::EVNT_TIM_ALRT);
    // short time period
    dispatcher::Event e1 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(42, 100), false };
    auto time_start = std::chrono::high_resolution_clock::now();
    client.send(e1, 20);
    dispatcher::Event rcv1 = client.recieve_event();
    auto time_end = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(time_end-time_start).count();
    ASSERT_TRUE(delta<110 && delta >=100);
    // long time period
    dispatcher::Event e2 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(42, 1500), false };
    time_start = std::chrono::high_resolution_clock::now();
    client.send(e2, 20);
    dispatcher::Event rcv2 = client.recieve_event();
    time_end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::milliseconds>(time_end-time_start).count();
    ASSERT_TRUE(delta<1510 && delta >=1500);
}

TEST(Timer, MultipleTimers) {
    dispatcher::Dispatcher disp("TEST_DISP_TIMER_MULTIPLE");
    timer::AsyncTimerService timer_svc("TEST_DISP_TIMER_MULTIPLE");
    TestClient client("TEST_DISP_TIMER_MULTIPLE", "TEST_CLIENT_TIMER_MULTIPLE");
    client.subscribe(dispatcher::EventType::EVNT_TIM_ALRT);
    // short time period
    dispatcher::Event e1 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(42, 100), false };
    dispatcher::Event e2 = { dispatcher::EventType::EVNT_TIM_REQ,
                dispatcher::Event::generate_timer_payload(23, 200), false };
    auto time_start = std::chrono::high_resolution_clock::now();
    client.send(e1, 20);
    client.send(e2, 20);
    dispatcher::Event rcv1 = client.recieve_event();
    auto time_end = std::chrono::high_resolution_clock::now();
    ASSERT_EQ(rcv1.payload, 42);
    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(time_end-time_start).count();
    ASSERT_TRUE(delta<110 && delta >=100);
    dispatcher::Event rcv2 = client.recieve_event();
    time_end = std::chrono::high_resolution_clock::now();
    ASSERT_EQ(rcv2.payload, 23);
    delta = std::chrono::duration_cast<std::chrono::milliseconds>(time_end-time_start).count();
    ASSERT_TRUE(delta<210 && delta >=200);
}
