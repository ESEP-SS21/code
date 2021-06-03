
#pragma once

#include <gtest/gtest.h>
#include "stm_test_client.h"
#include <logic/datamodel/unit_data.h>

namespace test {
namespace logic {
namespace stm {

template<typename Context>
class stm_test_base : public ::testing::Test {

#define INIT_STM_TEST(FixtureName, Context)\
class FixtureName : public stm_test_base<Context> {};

#define ASSERT_STATE(STATE) ASSERT_EQ(context.currentState(),STATE::name)

public:
    StmTestClient client;
    ::logic::datamodel::UnitData data;
    Context context{&client, &data};

    template<typename StateAfter>
    void test_transition_to(Event event, std::initializer_list<Event> expectedEvents = {}){

        context.handle(event);
        ASSERT_STATE(StateAfter);
        for (auto & expectedEvent : expectedEvents){
            ASSERT_EQ(client.get_last_event(), expectedEvent);
        }
        ASSERT_TRUE(client.empty());
    }
};


}
}
}
