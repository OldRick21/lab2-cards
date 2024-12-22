project(interface)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


add_compile_options(--coverage)
add_link_options(--coverage)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")

add_executable(${PROJECT_NAME} main_interface.cpp)

target_link_libraries(${PROJECT_NAME}
    card
)