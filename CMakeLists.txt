cmake_minimum_required(VERSION 3.29)
project(PartyThread)

set(CMAKE_CXX_STANDARD 20)

add_executable(PartyThreadsExample examples/PartyThreadsExample.cpp include/PartyThreads.h)

#
#   Google Test
#
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

#
#   Unit Test
#
set(UNIT_TEST PartyThreadsUnitTest)
add_executable(${UNIT_TEST} tests/PartyThreadsTest.cpp include/PartyThreads.h)

target_link_libraries(${UNIT_TEST}
        PRIVATE
        gtest
        gtest_main)

# Add a custom target that runs the test application
# BEWARE: it fails if the test fails
add_custom_target(RunTest
        COMMAND ${UNIT_TEST}
        DEPENDS ${UNIT_TEST}
        COMMENT "Running test application..."
        VERBATIM)

#
#   Unit Test as library
#

add_library(${UNIT_TEST}Lib STATIC 
        tests/AsLibrary/PartyThreadsLibrary.cpp
        tests/AsLibrary/PartyThreadsLibrary.h
        include/PartyThreads.h)

set(UNIT_TEST_LIBRARY PartyThreadsUnitTestLibrary)
add_executable(${UNIT_TEST_LIBRARY} tests/PartyThreadsLibraryTest.cpp tests/AsLibrary/PartyThreadsLibrary.h)

target_link_libraries(${UNIT_TEST_LIBRARY}
        PRIVATE
        ${UNIT_TEST}Lib
        gtest
        gtest_main)

# Add a custom target that runs the test application
# BEWARE: it fails if the test fails
add_custom_target(RunTestAsLibrary
        COMMAND ${UNIT_TEST_LIBRARY}
        DEPENDS ${UNIT_TEST_LIBRARY}
        COMMENT "Running test application..."
        VERBATIM)