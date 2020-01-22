cmake_minimum_required(VERSION 3.12.4)
project(EarlyAlgorithm)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()
add_executable(Test tests.cpp)

add_test(Test ${PROJECT_SOURCE_DIR}/bin/testing)

add_executable(EarlyAlgorithm main.cpp)

add_subdirectory(ParsersLibrary)
set(EXTRA_LIBS ${EXTRA_LIBS} ParsersLibrary)
SET(CMAKE_INSTALL_RPATH "${PROJECT_SOURCE_DIR}/bin")


target_link_libraries(EarlyAlgorithm ${EXTRA_LIBS})
target_link_libraries(Test ${EXTRA_LIBS})
target_link_libraries(Test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

set(CMAKE_EXE_LINKER_FLAGS --coverage)

add_definitions(-fprofile-arcs -ftest-coverage)
target_link_libraries(Test -fprofile-arcs)

