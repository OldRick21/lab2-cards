project(interface)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


add_compile_options(--coverage)
add_link_options(--coverage)

# Create the executable

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")

add_executable(${PROJECT_NAME} main_interface.cpp)


# Link the static library from subproject1 using its alias sub::lib1
# Link the header only library from subproject2 using its alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    card
)