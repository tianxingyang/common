cmake_minimum_required(VERSION 3.0)

set(GTEST_ROOT "../libs/")
set(GLOG_DIR "../libs/")

find_package(Threads)
find_package(GTest REQUIRED)

include_directories(../libs/)
include_directories(../libs/google)
include_directories(../utils/)

link_directories(${GLOG_DIR})

link_libraries(glog)

add_executable(vlist_test vlist_test.cpp)
target_link_libraries(vlist_test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(vlist_test Threads::Threads)
target_link_libraries(vlist_test glog)
