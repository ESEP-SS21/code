#pragma once
#include <string>
#include <gtest/gtest.h>
#include "spdlog/fmt/fmt.h"

namespace test {

#define __TC_NAME__ ::testing::UnitTest::GetInstance()->current_test_info()->name()

constexpr int msg_prio = 20;
const std::string dispatcherPrefix = "TEST_DISP";
const std::string clienetPrefix = "TEST_CLIENT";

struct utils{
    static std::string getUniqueDispatcherName(){
        static int i = 0;
        return fmt::format("{}_{}_{}", dispatcherPrefix, i++, __TC_NAME__);
    }
};

static inline std::string getUniqueDispatcherName() {
    return utils::getUniqueDispatcherName();
}



} /* namespace */
