project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib/google_test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
file(GLOB_RECURSE stm_SRC
        "../src/logic/stm/*.h"
        "../src/logic/stm/*.cpp"
        "../src/logic/datamodel/*.h"
        "../src/logic/datamodel/*.cpp"
        )

add_executable(Google_Tests_run
        ${stm_SRC}
        argument_parser_test.cpp
        logic/stm/temp.cpp
        logic/stm/stm_test_client.h
        logic/stm/stm_test_client.cpp

        ../src/dispatcher/Event.h
        ../src/dispatcher/IEventSender.h
        logic/stm/receive_workpiece_test.cpp
        logic/stm/stm_test_base.h)
target_link_libraries(Google_Tests_run gtest gtest_main)
