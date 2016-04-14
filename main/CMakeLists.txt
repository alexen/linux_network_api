add_executable(date_time_tcp_cli date_time_tcp_cli.c)
add_executable(date_time_tcp_srv date_time_tcp_srv.c)
add_executable(echo_tcp_srv01 echo_tcp_srv01.c)
add_executable(echo_tcp_cli01 echo_tcp_cli01.c)

target_link_libraries(date_time_tcp_cli
    error
    tools
)

target_link_libraries(date_time_tcp_srv
    error
    tools
)

target_link_libraries(echo_tcp_srv01
    error
    tools
)

target_link_libraries(echo_tcp_cli01
    error
    tools
)