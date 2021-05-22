#include "tests.h"
#include "../src/dispatcher/dispatcher.h"
#include "../src/timer/ASyncTimerService.h"
#include "../src/dispatcher/cnnMngmnt/QnxChannel.h"
#include "../src/dispatcher/cnnMngmnt/QnxConnection.h"
#include "../src/dispatcher/Event.h"
#include "TestClient.h"

TEST(Timer, ReturnedEventNumber) {
    dispatcher::Dispatcher disp("TEST_DISP");
    timer::AsyncTimerService timer_svc("TEST_DISP");
    TestClient client("TEST_DISP", "TEST_CLIENT");
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

