cmake_minimum_required(VERSION 3.14)
project(StackLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB MAIN_SOURCES "main.cpp")
add_executable(demo ${MAIN_SOURCES} src/memory_resource.cpp)

find_package(GTest REQUIRED)

add_executable(tests 
    tests/stack_test.cpp
    src/memory_resource.cpp
)

target_link_libraries(tests GTest::gtest GTest::gtest_main)

enable_testing()
add_test(NAME stack_tests COMMAND tests)
