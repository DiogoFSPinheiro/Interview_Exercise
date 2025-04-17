cmake_minimum_required(VERSION 3.10)
project(MultiThreadedQueue LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g -O1")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add a header-only interface library for the template
add_library(queue INTERFACE)
target_include_directories(queue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/srcs)


# Add test support
enable_testing()

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test target
add_executable(queue_tests tests/test_queue.cpp)
target_link_libraries(queue_tests
  PRIVATE
    queue
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(queue_tests)
