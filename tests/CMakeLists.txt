cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

set(GTEST_ROOT "../libs/")
set(GTEST_INCLUDE_DIR "../libs/")
set(SOURCE_FILES "vlist_test.cpp")
set(EXECUTABLE_TARGET "vlist_test")

find_package(Threads)
find_package(GTest REQUIRED)

include_directories(../libs/)
include_directories(../libs/google)
include_directories(../libs/easyloggingpp/)
include_directories(../utils/)

link_directories(../libs/)

link_libraries(easylogging++)

add_executable(${EXECUTABLE_TARGET} ${SOURCE_FILES})

target_link_libraries(${EXECUTABLE_TARGET} ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${EXECUTABLE_TARGET} Threads::Threads)
