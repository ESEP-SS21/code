#include "TestClient.h"
#include "../../dispatcher/Event.h"
#include "../../dispatcher/dispatcher.h"
#include "../TestUtils.h"
#include <array>

namespace test {
namespace dispatcher {

using namespace ::dispatcher;
constexpr int prio { 10 };

class SingleDispatcherTest: public ::testing::Test {
protected:
    std::unique_ptr<Dispatcher> _dispatcher;
    std::unique_ptr<TestClient> _testClientSender;
    std::unique_ptr<TestClient> _testClientReceiver;
    SingleDispatcherTest() {
        const std::string DISPATCHER_NAME { getUniqueDispatcherName() };
        _dispatcher = std::unique_ptr<Dispatcher>(new Dispatcher(DISPATCHER_NAME));
        _testClientSender = std::unique_ptr<TestClient>(
                new TestClient(DISPATCHER_NAME, fmt::format("{}_{}", clienetPrefix, __TC_NAME__)));
        _testClientReceiver = std::unique_ptr<TestClient>(
                new TestClient(DISPATCHER_NAME, fmt::format("{}_{}", clienetPrefix, __TC_NAME__)));
    }

    void test_type(bool broadcast) {
        EventType send_type {EventType::EVNT_ACT_BELT_STP};
        _testClientReceiver->subscribe(send_type);
        _testClientSender->send(Event(send_type, 1, broadcast), prio);
        ASSERT_EQ(send_type, _testClientReceiver->recieve_event().type);
    }

    void test_payload(bool broadcast) {
        int send_payload {33};
        const EventType send_type {EventType::EVNT_ACT_BELT_FWD};
        _testClientReceiver->subscribe(send_type);
        _testClientSender->send(Event(send_type, send_payload, false), prio);
        ASSERT_EQ(send_payload, _testClientReceiver->recieve_event().payload);
    }

    std::initializer_list<EventType> _test_event_types_actors {EventType::EVNT_ACT_BELT_FWD,
        EventType::EVNT_ACT_BELT_BWD, EventType::EVNT_ACT_BELT_STP,
        EventType::EVNT_ACT_STPL_LED_ON, EventType::EVNT_ACT_STPL_LED_OFF,
        EventType::EVNT_ACT_BELT_BWD, EventType::EVNT_ACT_BELT_STP,};

    std::initializer_list<EventType> _test_event_types_sensors {EventType::EVNT_SEN_LB_EN_CLR,
        EventType::EVNT_SEN_LB_EN_BLCK, EventType::EVNT_SEN_ESTOP_ON,
        EventType::EVNT_SEN_ESTOP_OFF, EventType::EVNT_SEN_HEIGHT_HE,
        EventType::EVNT_SEN_HEIGHT_REQ, EventType::EVNT_SEN_LB_EN_BLCK};
};

TEST_F(SingleDispatcherTest, ReceivedEventTypeShouldEqualSendEventType) {
    test_type(false);
}

TEST_F(SingleDispatcherTest, ReceivedPayloadShouldEqualSendPayload) {
    test_payload(false);
}

TEST_F(SingleDispatcherTest, BroadcastShouldNotEffectResult) {
    test_payload(true);
    test_type(true);
}

TEST_F(SingleDispatcherTest, ClientShouldReceiveOwnEvents) {
    EventType et_receiver { EventType::EVNT_ACT_BELT_STP };
    EventType et_sender { EventType::EVNT_SEN_ESTOP_ON };
    _testClientReceiver->subscribe( { et_receiver, et_sender });

    _testClientReceiver->send( { et_receiver, 1, false }, prio);
    _testClientSender->send( { et_sender, 1, false }, prio);

    ASSERT_EQ(et_receiver, _testClientReceiver->recieve_event().type);
    ASSERT_EQ(et_sender, _testClientReceiver->recieve_event().type);
}

TEST_F(SingleDispatcherTest, MultipleEventsShouldArriveInCorrectOrder) {
    _testClientReceiver->subscribe(_test_event_types_actors);

    for (EventType event_type : _test_event_types_actors) {
        _testClientSender->send( { event_type, 1, false }, prio);
    }

    for (EventType event_type : _test_event_types_actors) {
        ASSERT_EQ(event_type, _testClientReceiver->recieve_event().type);
    }
}

TEST_F(SingleDispatcherTest, BothClientsShouldBeAbleToSendAndReceive) {
    auto &client_listening_to_sensors { _testClientSender };
    auto &client_listening_to_actors { _testClientReceiver };

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

TEST_F(SingleDispatcherTest, OnlySubscribedEventsShouldBeReceived) {
    _testClientReceiver->subscribe(_test_event_types_actors);
    EventType actor_event { *_test_event_types_actors.begin() };

    _testClientSender->send( { *_test_event_types_sensors.begin(), 1, false }, prio);
    _testClientSender->send( { actor_event, 1, false }, prio);

    ASSERT_EQ(actor_event, _testClientReceiver->recieve_event().type);
}

} /*namespace*/
} /*namespace*/
