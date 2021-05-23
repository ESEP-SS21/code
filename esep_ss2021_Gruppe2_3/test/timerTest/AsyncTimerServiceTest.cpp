#include "TestClient.h"
#include "tests.h"
#include "../src/dispatcher/Event.h"

#include <chrono>
#include <string>

using namespace dispatcher;

namespace test {
namespace timerTest {

constexpr int timerToleranceMs = 10;
const std::string dispatcherPrefix = "TEST_DISP";
const std::string clienetPrefix = "TEST_CLIENT";

#define __TC_NAME__ ::testing::UnitTest::GetInstance()->current_test_info()->name()

std::string getUniqueDispatcherName() {
    static int i = 0;
    return fmt::format("{}_{}_{}", dispatcherPrefix, i++, __TC_NAME__);
}

bool timeIsWithinTolerance(long expected, long actual) {
    return (actual < expected + timerToleranceMs && actual >= expected);
}

struct TimerData {
    int ms_time;
    int payload;
};

class TimerTest: public ::testing::Test {
protected:
    std::unique_ptr<Dispatcher> _dispatcher;
    std::unique_ptr<timer::AsyncTimerService> _timerService;
    std::unique_ptr<TestClient> _testClient;
    TimerTest() {
        const std::string DISPATCHER_NAME = getUniqueDispatcherName();
        _dispatcher = std::unique_ptr<Dispatcher>(new Dispatcher(DISPATCHER_NAME));
        _timerService = std::unique_ptr<timer::AsyncTimerService>(
                new timer::AsyncTimerService(DISPATCHER_NAME));
        _testClient = std::unique_ptr<TestClient>(
                new TestClient(DISPATCHER_NAME, fmt::format("{}_{}", clienetPrefix, __TC_NAME__)));
        _testClient->subscribe( { dispatcher::EventType::EVNT_CTRL_T_STR_PRS_SRT,
                dispatcher::EventType::EVNT_TIM_ALRT });
    }

    void testSingleTimerEventCode(TimerData timer) {

        dispatcher::Event e1 = Event::CreateTimer(timer.payload, timer.ms_time);

        int msg_pio = 20;
        _testClient->send(e1, msg_pio);
        Event rcv = _testClient->recieve_event();
        ASSERT_EQ(rcv.payload, timer.payload);
    }

    void testSingleTimerTimePeriod(TimerData timer) {
        dispatcher::Event e1 = Event::CreateTimer(timer.payload, timer.ms_time);

        auto time_start = std::chrono::high_resolution_clock::now();
        this->_testClient->send(e1, 20);
        this->_testClient->recieve_event();
        auto time_end = std::chrono::high_resolution_clock::now();
        auto actual_ms_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                time_end - time_start).count();

        timeIsWithinTolerance(timer.ms_time, actual_ms_time);
    }

    void testMultipleTimerTimePeriod(TimerData timer1, TimerData timer2) {
        dispatcher::Event e1 = Event::CreateTimer(timer1.payload, timer1.ms_time);
        dispatcher::Event e2 = Event::CreateTimer(timer2.payload, timer2.ms_time);

        auto time_start = std::chrono::high_resolution_clock::now();
        this->_testClient->send(e1, 20);
        this->_testClient->send(e2, 20);

        dispatcher::Event rcv1 = this->_testClient->recieve_event();
        auto time_end = std::chrono::high_resolution_clock::now();
        ASSERT_EQ(rcv1.payload, timer1.payload);
        auto actual_ms_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                time_end - time_start).count();
        timeIsWithinTolerance(timer1.ms_time, actual_ms_time);

        dispatcher::Event rcv2 = this->_testClient->recieve_event();
        time_end = std::chrono::high_resolution_clock::now();
        ASSERT_EQ(rcv2.payload, timer2.payload);
        actual_ms_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                time_end - time_start).count();
        timeIsWithinTolerance(timer2.ms_time, actual_ms_time);
    }
};

TEST_F(TimerTest, ReturnedEventShouldEqualExpectedEventCode) {
    this->testSingleTimerEventCode( { 10, 44 });
    this->testSingleTimerEventCode( { 10, 45 });
    this->testSingleTimerEventCode( { 10, 44 });
}

TEST_F(TimerTest, TimePeriodShouldBeWithinTolerance) {
    this->testSingleTimerTimePeriod( { 50, 44 });
    this->testSingleTimerTimePeriod( { 1500, 44 });
}

TEST_F(TimerTest, TimePeriodShouldBeWithinToleranceWithMultipleTimers) {
    this->testMultipleTimerTimePeriod( { 100, 42 }, { 200, 43 });
}

} /*namespace*/
} /*namespace*/
