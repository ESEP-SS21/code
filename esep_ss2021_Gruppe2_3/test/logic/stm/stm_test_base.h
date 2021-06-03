
#pragma once

#include <gtest/gtest.h>
#include "stm_test_client.h"
#include <logic/datamodel/unit_data.h>


class stm_test_base : public ::testing::Test {

#define ASSERT_STATE(STATE) ASSERT_EQ(context.currentState(),STATE::name)
public:
    std::shared_ptr<StmTestClient> client = std::make_shared<StmTestClient>();
    std::shared_ptr<logic::datamodel::UnitData> data = std::make_shared<logic::datamodel::UnitData>();
};



