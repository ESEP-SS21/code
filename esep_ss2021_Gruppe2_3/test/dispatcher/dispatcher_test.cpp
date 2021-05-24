#include "TestClient.h"
#include "../../dispatcher/Event.h"
#include "../../dispatcher/dispatcher.h"
#include "../TestUtils.h"
#include <array>

namespace test {
namespace dispatcher {

using namespace ::dispatcher;
constexpr int prio { 10 };

class DispatcherTest: public ::testing::Test {
protected:
    std::unique_ptr<Dispatcher> _dispatcher1;
    std::unique_ptr<Dispatcher> _dispatcher2;
    std::unique_ptr<TestClient> _client_dis1_sender;
    std::unique_ptr<TestClient> _client_dis1_receiver;
    std::unique_ptr<TestClient> _client_dis2;
    DispatcherTest() {
        const std::string DISPATCHER_NAME_1 { getUniqueDispatcherName() };
        const std::string DISPATCHER_NAME_2 { getUniqueDispatcherName() };

        _dispatcher1 = std::unique_ptr<Dispatcher>(new Dispatcher(DISPATCHER_NAME_1));
        _dispatcher2 = std::unique_ptr<Dispatcher>(new Dispatcher(DISPATCHER_NAME_2));

        _dispatcher2->connect_to_other(DISPATCHER_NAME_1);
        _dispatcher1->connect_to_other(DISPATCHER_NAME_2);

        _client_dis1_sender = std::unique_ptr<TestClient>(
                new TestClient(DISPATCHER_NAME_1, fmt::format("{}_{}_{}", clienetPrefix, __TC_NAME__,
        "_client_dis1_sender")));

        _client_dis1_receiver = std::unique_ptr<TestClient>(
                new TestClient(DISPATCHER_NAME_1, fmt::format("{}_{}_{}", clienetPrefix, __TC_NAME__,
        "_client_dis1_receiver")));

        _client_dis2 = std::unique_ptr<TestClient>(
                new TestClient(DISPATCHER_NAME_2, fmt::format("{}_{}_{}", clienetPrefix, __TC_NAME__,
        "_client_dis2")));
    }

    void TestType(bool broadcast) {
        EventType send_type {EventType::EVNT_ACT_BELT_STP};
        _client_dis1_receiver->subscribe(send_type);
        _client_dis1_sender->send(Event(send_type, 1, broadcast), prio);
        ASSERT_EQ(send_type, _client_dis1_receiver->recieve_event().type);
    }

    void TestPayload(bool broadcast) {
        int send_payload {33};
        const EventType send_type {EventType::EVNT_ACT_BELT_FWD};
        _client_dis1_receiver->subscribe(send_type);
        _client_dis1_sender->send(Event(send_type, send_payload, false), prio);
        ASSERT_EQ(send_payload, _client_dis1_receiver->recieve_event().payload);
    }

    std::initializer_list<EventType> _test_event_types_actors {EventType::EVNT_ACT_BELT_FWD,
        EventType::EVNT_ACT_BELT_BWD, EventType::EVNT_ACT_BELT_STP, EventType::EVNT_ACT_STPL_LED_ON,
        EventType::EVNT_ACT_STPL_LED_OFF, EventType::EVNT_ACT_BELT_BWD, EventType::EVNT_ACT_BELT_STP,};

    std::initializer_list<EventType> _test_event_types_sensors {EventType::EVNT_SEN_LB_EN_CLR,
        EventType::EVNT_SEN_LB_EN_BLCK, EventType::EVNT_SEN_ESTOP_ON, EventType::EVNT_SEN_ESTOP_OFF,
        EventType::EVNT_SEN_HEIGHT_HE, EventType::EVNT_SEN_HEIGHT_REQ,
        EventType::EVNT_SEN_LB_EN_BLCK};
};

TEST_F(DispatcherTest, ReceivedEventTypeShouldEqualSendEventType) {
    TestType(false);
}

TEST_F(DispatcherTest, ReceivedPayloadShouldEqualSendPayload) {
    TestPayload(false);
}

TEST_F(DispatcherTest, BroadcastShouldNotEffectResult) {
    TestPayload(true);
    TestType(true);
}

TEST_F(DispatcherTest, ClientShouldReceiveOwnEvents) {
    EventType et_receiver { EventType::EVNT_ACT_BELT_STP };
    EventType et_sender { EventType::EVNT_SEN_ESTOP_ON };
    _client_dis1_receiver->subscribe( { et_receiver, et_sender });

    _client_dis1_receiver->send( { et_receiver, 1, false }, prio);
    _client_dis1_sender->send( { et_sender, 1, false }, prio);

    ASSERT_EQ(et_receiver, _client_dis1_receiver->recieve_event().type);
    ASSERT_EQ(et_sender, _client_dis1_receiver->recieve_event().type);
}

TEST_F(DispatcherTest, MultipleEventsShouldArriveInCorrectOrder) {
    _client_dis1_receiver->subscribe(_test_event_types_actors);

    for (EventType event_type : _test_event_types_actors) {
        _client_dis1_sender->send( { event_type, 1, false }, prio);
    }

    for (EventType event_type : _test_event_types_actors) {
        ASSERT_EQ(event_type, _client_dis1_receiver->recieve_event().type);
    }
}

TEST_F(DispatcherTest, BothClientsShouldBeAbleToSendAndReceive) {
    auto &client_listening_to_sensors { _client_dis1_sender };
    auto &client_listening_to_actors { _client_dis1_receiver };

    client_listening_to_actors->subscribe(_test_event_types_actors);
    client_listening_to_sensors->subscribe(_test_event_types_sensors);

    for (EventType actor_event_types : _test_event_types_actors)
        client_listening_to_sensors->send( { actor_event_types, 1, false }, prio);
    for (EventType sensor_event_types : _test_event_types_sensors)
        client_listening_to_actors->send( { sensor_event_types, 1, false }, prio);

    for (EventType actor_event_type : _test_event_types_actors)
        ASSERT_EQ(actor_event_type, client_listening_to_actors->recieve_event().type);
    for (EventType actor_event_type : _test_event_types_sensors)
        ASSERT_EQ(actor_event_type, client_listening_to_sensors->recieve_event().type);
}

TEST_F(DispatcherTest, OnlySubscribedEventsShouldBeReceived) {
    _client_dis1_receiver->subscribe(_test_event_types_actors);
    EventType actor_event { *_test_event_types_actors.begin() };

    _client_dis1_sender->send( { *_test_event_types_sensors.begin(), 1, false }, prio);
    _client_dis1_sender->send( { actor_event, 1, false }, prio);

    ASSERT_EQ(actor_event, _client_dis1_receiver->recieve_event().type);
}

TEST_F(DispatcherTest, BroadcastShouldSendEventToOtherDispatcher) {
    EventType et = EventType::EVNT_HRTB;
    int payload = 44;

    _client_dis1_receiver->subscribe(et);
    _client_dis2->send( { et, payload, true }, prio);

    auto rec_ev = _client_dis1_receiver->recieve_event();

    ASSERT_EQ(et, rec_ev.type);
    ASSERT_EQ(payload, rec_ev.payload);
}

TEST_F(DispatcherTest, NoBroadcastShouldNotSendEventToOtherDispatcher) {
    int wrong_payload = 44;
    int correct_payload = 22;
    EventType et = EventType::EVNT_ACT_BELT_STP;

    _client_dis1_receiver->subscribe(et);
    _client_dis2->send( { et, wrong_payload, false }, prio);
    _client_dis2->send( { et, correct_payload, true }, prio);

    ASSERT_EQ(correct_payload, _client_dis1_receiver->recieve_event().payload);
}

} /*namespace*/
} /*namespace*/
