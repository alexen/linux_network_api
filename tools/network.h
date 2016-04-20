/*
 * net.h
 *
 * Содержит описания вспомогательных утилит связанных с сокетами, сетью и т.п.
 *
 */

#ifndef TOOLS_NETWORK_H_
#define TOOLS_NETWORK_H_

#include <netinet/in.h>


int sockfd_to_family( int sockfd );
int set_sockaddr_ipv4( struct sockaddr_in* sockaddr, const char* addr, int port );
int create_bound_socket_ipv4( int socktype, const char* addr, int port );
int create_connected_socket_ipv4( const char* addr, int port );
int create_listened_socket_ipv4( const char* addr, int port );


#endif /* TOOLS_NETWORK_H_ */
