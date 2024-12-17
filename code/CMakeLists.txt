cmake_minimum_required(VERSION 3.16)

set(CMAKE_OSX_ARCHITECTURES x86_64)

project(lab2)

set(CMAKE_CXX_STANDARD 23)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# set(CMAKE_INSTALL_PREFIX "../build")

add_subdirectory(test)
add_subdirectory(src)
add_subdirectory(interface)

enable_testing()






