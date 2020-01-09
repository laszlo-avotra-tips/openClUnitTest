cmake_minimum_required (VERSION 2.8)
project (turtle-test)

set (gtest_disable_pthreads on)

add_subdirectory (googletest-master)
config_compiler_and_linker()

add_executable (${PROJECT_NAME} mock_turtle_test.cpp)
target_link_libraries (${PROJECT_NAME} gtest gmock)
