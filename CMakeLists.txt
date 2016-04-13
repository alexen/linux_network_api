cmake_minimum_required(VERSION 3.4)

add_definitions(-std=c99)
add_definitions(-Wall -Wpedantic -Werror)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(error)
add_subdirectory(tools)
add_subdirectory(main)