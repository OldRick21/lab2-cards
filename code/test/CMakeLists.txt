cmake_minimum_required(VERSION 3.16)

set(CMAKE_OSX_ARCHITECTURES x86_64)

project(lab2_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

find_package(Catch2 REQUIRED)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")



enable_testing()

add_compile_options(--coverage)
add_link_options(--coverage)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")

add_executable(lab2_test source/CardTests.cpp source/CardDeckTests.cpp source/test-main.cpp)

target_link_libraries(
        lab2_test
        PRIVATE
        card
        Catch2::Catch2
)

list(APPEND CMAKE_MODULE_PATH cmake-build-debug/_deps/catch2-src/extras)
include(CTest)
include(Catch)
catch_discover_tests(lab2_test)