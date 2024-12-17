cmake_minimum_required(VERSION 3.16)

project(card_library)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_compile_options(--coverage)
add_link_options(--coverage)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")

add_library(card STATIC
        card/Card.cpp
        card-deck/CardDeck.cpp
        )

target_include_directories(card PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/card
        ${CMAKE_CURRENT_SOURCE_DIR}/card-deck
        )