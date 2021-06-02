project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib/google_test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run
        argument_parser_test.cpp
        ../src/logic/stm/base_context.h
        ../src/logic/stm/base_base_state.h
        ../src/dispatcher/Event.h
        ../src/dispatcher/IEventSender.h
        ../src/logic/stm/testStm/test_context.h
        ../src/logic/stm/testStm/test_context.cpp
        ../src/logic/stm/testStm/test_base_state.h
        logic/stm/temp.cpp
        logic/stm/stm_test_client.h
        logic/stm/stm_test_client.cpp
        ../src/logic/stm/testStm/states/state_a.h
        ../src/logic/stm/testStm/states/state_a.cpp
        ../src/logic/stm/testStm/states/state_b.h
        ../src/logic/stm/testStm/states/state_b.cpp
        ../src/logic/stm/testStm/states/state_c.h
        ../src/logic/stm/testStm/states/state_c.cpp
        ../src/logic/stm/testStm/states/default.h


        )
target_link_libraries(Google_Tests_run gtest gtest_main)
