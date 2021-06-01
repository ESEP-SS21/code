#include "TestUtils.h"
#include "ArgumentParser.hpp"

TEST(ArgumentParser, Test1) {

    std::string filename = "file";

    constexpr int size = 3;
    const char *messages[size] =
        {
            "testmain",
            "-P",
            filename.c_str()
        };

    auto res = argument_parser::parse(size, messages);
    ASSERT_TRUE(res->playback);
    ASSERT_EQ(res->filename, filename);

}