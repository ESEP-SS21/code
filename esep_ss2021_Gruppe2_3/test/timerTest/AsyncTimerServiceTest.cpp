#include "TestClient.h"
#include "../../dispatcher/Event.h"
#include "../../dispatcher/dispatcher.h"
#include "../../timer/AsyncTimerService.h"
#include "../TestUtils.h"

#include <chrono>
#include <string>

namespace test {
namespace timerTest {

using namespace dispatcher;
using ms = std::chrono::milliseconds;
using clock = std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

constexpr int timerToleranceMs = 10;

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
        _testClient->subscribe( { EventType::EVNT_CTRL_T_STR_PRS_SRT, EventType::EVNT_TIM_ALRT });
    }

    void testSingleTimerEventCode(TimerData timer) {
        Event e1 = Event::CreateTimer(timer.payload, timer.ms_time);

        _testClient->send(e1, msg_prio);
        Event rcv = _testClient->recieve_event();
        ASSERT_EQ(timer.payload, rcv.payload);
    }

    void testSingleTimerTimePeriod(TimerData timer) {
        Event e1 = Event::CreateTimer(timer.payload, timer.ms_time);

        auto time_start = clock::now();
        this->_testClient->send(e1, msg_prio);
        this->_testClient->recieve_event();
        auto time_end = clock::now();
        auto actual_ms_time = duration_cast<ms>(time_end - time_start).count();

        timeIsWithinTolerance(timer.ms_time, actual_ms_time);
    }

    void testMultipleTimerTimePeriod(TimerData timer1, TimerData timer2) {
        Event e1 = Event::CreateTimer(timer1.payload, timer1.ms_time);
        Event e2 = Event::CreateTimer(timer2.payload, timer2.ms_time);

        auto time_start = clock::now();
        this->_testClient->send(e1, msg_prio);
        this->_testClient->send(e2, msg_prio);

        Event rcv1 = this->_testClient->recieve_event();
        auto time_end = clock::now();
        ASSERT_EQ(timer1.payload, rcv1.payload);
        auto actual_ms_time = duration_cast<ms>(time_end - time_start).count();
        timeIsWithinTolerance(timer1.ms_time, actual_ms_time);

        Event rcv2 = this->_testClient->recieve_event();
        time_end = clock::now();
        ASSERT_EQ(timer2.payload, rcv2.payload);
        actual_ms_time = duration_cast<ms>(time_end - time_start).count();
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
