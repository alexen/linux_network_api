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