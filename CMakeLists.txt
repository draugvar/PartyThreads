cmake_minimum_required(VERSION 3.29)
project(PartyThread)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
add_executable(PartyThread examples/PartyThreadsExample.cpp)

#
#   Google Test
#
set(UNIT_TEST UnitTest)
add_executable(${UNIT_TEST} ${CMAKE_CURRENT_SOURCE_DIR}/tests/PartyThreadsTest.cpp)

include(FetchContent)
option(BUILD_GMOCK "Build Google test's GMock?" OFF)
option(INSTALL_GMOCK "Install Google test's GMock?" OFF)
option(INSTALL_GTEST "Install Google test's GTest?" OFF)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main
)

FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(${UNIT_TEST}
        PRIVATE
        gtest
        gtest_main)
