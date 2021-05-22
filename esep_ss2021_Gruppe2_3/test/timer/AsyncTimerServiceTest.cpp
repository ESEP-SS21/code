#include "tests.h"
#include "../src/dispatcher/dispatcher.h"
#include "../src/timer/ASyncTimerService.h"
#include "../src/dispatcher/cnnMngmnt/QnxChannel.h"
#include "../src/dispatcher/cnnMngmnt/QnxConnection.h"
#include "../src/dispatcher/Event.h"
#include "TestClient.h"
#include <chrono>
#include <string>

using namespace dispatcher;

constexpr int timerToleranceMs = 10;
const std::string dispatcherPrefix = "TEST_DISP";
const std::string clienetPrefix = "TEST_CLIENT";

std::string getUniqueDispatcherName(std::string name) {
    static int i = 0;
    return fmt::format("{}_{}_{}", dispatcherPrefix, i++, name);
}

class TimerTest: public ::testing::Test {
protected:
    std::unique_ptr<Dispatcher> _dispatcher;
    std::unique_ptr<timer::AsyncTimerService> _timerService;
    std::unique_ptr<TestClient> _testClient;
    TimerTest() {
        const std::string DISPATCHER_NAME = getUniqueDispatcherName(__FUNCTION__);
        _dispatcher = std::unique_ptr<Dispatcher>(new Dispatcher(DISPATCHER_NAME));
        _timerService = std::unique_ptr<timer::AsyncTimerService>(
                new timer::AsyncTimerService(DISPATCHER_NAME));
        _testClient = std::unique_ptr<TestClient>(
                new TestClient(DISPATCHER_NAME, fmt::format("{}_{}", clienetPrefix, __FUNCTION__)));
        _testClient->subscribe(EventType::EVNT_TIM_ALRT);
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    void testSingleTimerEventCode(int ms_time, int payload) {

        dispatcher::Event e1 = { dispatcher::EventType::EVNT_TIM_REQ, Event::generate_timer_payload(
                payload, ms_time), false };

        int msg_pio = 20;
        _testClient->send(e1, msg_pio);
        Event rcv = _testClient->recieve_event();
        ASSERT_EQ(rcv.payload, payload);
    }

    void testSingleTimerTimePeriod(int ms_time, int payload) {
        dispatcher::Event e1 = { dispatcher::EventType::EVNT_TIM_REQ,
                dispatcher::Event::generate_timer_payload(42, ms_time), false };

        auto time_start = std::chrono::high_resolution_clock::now();
        this->_testClient->send(e1, 20);
        this->_testClient->recieve_event();
        auto time_end = std::chrono::high_resolution_clock::now();
        auto actual_ms_time =
                std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();

        ASSERT_TRUE(actual_ms_time < ms_time + timerToleranceMs && actual_ms_time >= ms_time);
    }
};

TEST_F(TimerTest, ReturnedEventShouldEqualExpectedEventCode) {
    this->testSingleTimerEventCode(10, 44);
    this->testSingleTimerEventCode(10, 45);
    this->testSingleTimerEventCode(10, 44);
}

TEST_F(TimerTest, TimePeriodShouldBeWithinTolerance) {
    this->testSingleTimerTimePeriod(50, 44);
    this->testSingleTimerTimePeriod(1500, 44);
}

TEST_F(TimerTest, MultipleTimers) {
    int payload1 = 42;
    int payload2 = 23;
    int expectedTimeShort = 100;
    int expectedTimeLong = 200;

    dispatcher::Event e1 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(payload1, expectedTimeShort), false };
    dispatcher::Event e2 = { dispatcher::EventType::EVNT_TIM_REQ,
            dispatcher::Event::generate_timer_payload(payload2, expectedTimeLong), false };

    auto time_start = std::chrono::high_resolution_clock::now();
    this->_testClient->send(e1, 20);
    this->_testClient->send(e2, 20);

    dispatcher::Event rcv1 = this->_testClient->recieve_event();
    auto time_end = std::chrono::high_resolution_clock::now();
    ASSERT_EQ(rcv1.payload, payload1);
    auto actual_ms_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
    ASSERT_TRUE(actual_ms_time < expectedTimeShort + timerToleranceMs && actual_ms_time >= expectedTimeShort);

    dispatcher::Event rcv2 = this->_testClient->recieve_event();
    time_end = std::chrono::high_resolution_clock::now();
    ASSERT_EQ(rcv2.payload, payload2);
    actual_ms_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
    ASSERT_TRUE(actual_ms_time < expectedTimeLong + timerToleranceMs && actual_ms_time >= expectedTimeLong);
}
