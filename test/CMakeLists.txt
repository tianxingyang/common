cmake_minimum_required(VERSION 3.0)

set(GTEST_ROOT "../libs/")
set(GLOG_DIR "../libs/")
set(SOURCE_FILES "vlist_test.cpp")
set(EXECUTABLE_TARGET "vlist_test")

find_package(Threads)
find_package(GTest REQUIRED)

include_directories(../libs/)
include_directories(../libs/google)
include_directories(../utils/)

link_directories(${GLOG_DIR})

# link_libraries(glog)

add_executable(${EXECUTABLE_TARGET} ${SOURCE_FILES})

target_link_libraries(${EXECUTABLE_TARGET} ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${EXECUTABLE_TARGET} Threads::Threads)
target_link_libraries(${EXECUTABLE_TARGET} glog)
