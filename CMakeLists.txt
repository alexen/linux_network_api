cmake_minimum_required(VERSION 3.4)

add_definitions(-std=c99)
add_definitions(-Wall -Wpedantic -Werror)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(error)
add_subdirectory(tools)

add_executable(date_time_tcp_cli date_time_tcp_cli.c)
add_executable(date_time_tcp_srv date_time_tcp_srv.c)

target_link_libraries(date_time_tcp_cli
    error
    tools
)

target_link_libraries(date_time_tcp_srv
    error
    tools
)