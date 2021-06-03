
#pragma once

#include <gtest/gtest.h>
#include "stm_test_client.h"
#include <logic/datamodel/unit_data.h>


template<typename Context>
class stm_test_base : public ::testing::Test {

#define INIT_STM_TEST(FixtureName, Context)\
class FixtureName : public stm_test_base<Context> {};

#define ASSERT_STATE(STATE) ASSERT_EQ(context.currentState(),STATE::name)

public:
    StmTestClient client;
    logic::datamodel::UnitData data;
    Context context{&client, &data};
};



