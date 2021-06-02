project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib/google_test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run argument_parser_test.cpp ../src/logic/stm/base_context.cpp ../src/logic/stm/base_context.hpp)
target_link_libraries(Google_Tests_run gtest gtest_main)
