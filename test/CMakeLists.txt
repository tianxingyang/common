cmake_minimum_required(VERSION 3.0)

set(GTEST_ROOT "../libs/")

find_package(GTest REQUIRED)
include_directories(../libs/)
include_directories(../libs/google)
include_directories(../utils/)

add_executable(vlist_test vlist_test.cpp)
target_link_libraries(vlist_test ${GTEST_BOTH_LIBRARIES})
