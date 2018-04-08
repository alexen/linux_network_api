add_executable(date_time_tcp_cli date_time_tcp_cli.c)
target_link_libraries(date_time_tcp_cli error tools)

add_executable(date_time_tcp_srv date_time_tcp_srv.c)
target_link_libraries(date_time_tcp_srv error tools)

add_executable(echo_tcp_srv01 echo_tcp_srv01.c)
target_link_libraries(echo_tcp_srv01 error tools)

add_executable(echo_tcp_cli01 echo_tcp_cli01.c)
target_link_libraries(echo_tcp_cli01 error tools)

add_executable(echo_tcp_srv_select01 echo_tcp_srv_select01.c)
target_link_libraries(echo_tcp_srv_select01 error tools)

add_executable(echo_tcp_srv_poll01 echo_tcp_srv_poll01.c)
target_link_libraries(echo_tcp_srv_poll01 error tools)

add_executable(echo_udp_srv01 echo_udp_srv01.c)
target_link_libraries(echo_udp_srv01 error tools)

add_executable(echo_udp_cli01 echo_udp_cli01.c)
target_link_libraries(echo_udp_cli01 error tools)

add_executable(gethostbyname gethostbyname.c)