cmake_minimum_required(VERSION 3.14)
project(code-forge)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)

# Add source files
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Add running folder
option(key "Code key e.g 112A" OFF)
if (NOT key)
    message(FATAL_ERROR "Please provide a key using -Dkey=112A")
endif()


# Create runner
add_executable(test_runner ${key}/test.cpp ${key}/main.cpp)
target_compile_definitions(test_runner PRIVATE IGNORE_MAIN)
target_link_libraries(test_runner GTest::gtest_main)
add_test(NAME test_runner COMMAND test_runner)