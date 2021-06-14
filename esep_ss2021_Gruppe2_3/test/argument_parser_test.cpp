#include "TestUtils.h"
#include "argument_parser.hpp"

TEST(ArgumentParser, Playback) {
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

TEST(ArgumentParser, RecordPrimary) {
    std::string filename = "file";
    constexpr int size = 2;
    std::string filename_arg = "--record=" + filename;
    const char *messages[size] =
        {
            "testmain",
            filename_arg.c_str()
        };
    auto res = argument_parser::parse(size, messages);
    ASSERT_TRUE(res->record);
    ASSERT_FALSE(res->mode.secondary);
    ASSERT_EQ(res->filename, filename);
}

TEST(ArgumentParser, RecordDefaultValue) {
    constexpr int size = 2;
    const char *messages[size] =
        {
            "testmain",
            "-R",
        };
    auto res = argument_parser::parse(size, messages);
    ASSERT_TRUE(res->record);
    ASSERT_FALSE(res->mode.secondary);
    ASSERT_EQ(res->filename, "");
}

TEST(ArgumentParser, RecordSecondary) {
    std::string filename = "file";
    std::string filename_arg = "--record=" + filename;
    constexpr int size = 3;
    const char *messages[size] =
        {
            "testmain",
            "-s",
            filename_arg.c_str()
        };
    auto res = argument_parser::parse(size, messages);
    ASSERT_TRUE(res->record);
    ASSERT_TRUE(res->mode.secondary);
    ASSERT_EQ(res->filename, filename);
}

TEST(ArgumentParser, Secondary) {
    constexpr int size = 2;
    const char *messages[size] =
        {
            "testmain",
            "-s",
        };
    auto res = argument_parser::parse(size, messages);
    ASSERT_TRUE(res->mode.secondary);
}

TEST(ArgumentParser, Ejector) {
    constexpr int size = 2;
    const char *messages[size] =
        {
            "testmain",
            "-e",
        };
    auto res = argument_parser::parse(size, messages);
    ASSERT_TRUE(res->ejector);
}

TEST(ArgumentParser, Verbose) {
    constexpr int size = 2;
    const char *messages[size] =
        {
            "testmain",
            "-v",
        };
    auto res = argument_parser::parse(size, messages);
    ASSERT_TRUE(res->verbose);
}

TEST(ArgumentParser, Single) {
    constexpr int size = 2;
    const char *messages[size] =
        {
            "testmain",
            "--single",
        };
    auto res = argument_parser::parse(size, messages);
    ASSERT_TRUE(res->single);
}
