/*
 * network.c
 *
 */

#include <tools/wrapfunc.h>

#include <errno.h>
#include <stdlib.h> /* for atoi(), getenv() */
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <error/error.h>
#include <common/const.h>


void wrp_inet_pton( int af, const char* src, void* dst )
{
     const int rc = inet_pton( af, src, dst );
     if( rc < 0 )
          err_sys( "inet_pton error" );
     if( rc == 0 )
          err_quit( "inet_pton error: invalid network address %s", src );
}


int wrp_socket( int domain, int type, int protocol )
{
     const int sockfd = socket( domain, type, protocol );
     if( sockfd < 0 )
          err_sys( "socket error" );
     return sockfd;
}


void wrp_connect( int sockfd, const struct sockaddr* addr, socklen_t addrlen )
{
     if( connect( sockfd, addr, addrlen ) < 0 )
          err_sys( "connect error" );
}


void wrp_bind( int sockfd, const struct sockaddr* addr, socklen_t addrlen )
{
     if( bind( sockfd, addr, addrlen ) < 0 )
          err_sys( "bind error" );
}


void wrp_listen( int sockfd, int backlog )
{
     const char* externalBacklog = getenv( "LISTENQ" );

     if( externalBacklog )
          backlog = atoi( externalBacklog );

     if( listen( sockfd, backlog ) < 0 )
          err_sys( "listen error" );
}


int wrp_accept( int sockfd, struct sockaddr* addr, socklen_t* addrlen )
{
     const int acpt_sock = accept( sockfd, addr, addrlen );
     if( acpt_sock < 0 )
          err_sys( "accept error" );
     return acpt_sock;
}


int sockfd_to_family( int sockfd )
{
     union {
          struct sockaddr sa;
          char data[ MAXSOCKADDR ];
     }
     un = {{ 0 }};

     socklen_t len = MAXSOCKADDR;

     if( getsockname( sockfd, (struct sockaddr*) &un.data, &len ) < 0 )
          return -1;

     return un.sa.sa_family;
}


int set_sockaddr_ipv4( struct sockaddr_in* sockaddr, const char* addr, int port )
{
     sockaddr->sin_family = AF_INET;
     sockaddr->sin_port = htons( port );
     if( strcmp( addr, "*" ) == 0 )
     {
          sockaddr->sin_addr.s_addr = htonl( INADDR_ANY );
          return 0;
     }

     const int rc = inet_pton( AF_INET, addr, &sockaddr->sin_addr );
     if( rc == 0 )
     {
          errno = EINVAL;
          return -1;
     }
     return 0;
}


void wrp_set_sockaddr_v4( struct sockaddr_in* sockaddr, const char* addr, int port )
{
     if( set_sockaddr_ipv4( sockaddr, addr, port ) < 0 )
          err_sys( "set_sockaddr_v4 error" );
}


int create_connected_socket_ipv4( const char* addr, int port )
{
     struct sockaddr_in sa = { 0 };
     const int sockfd = socket( AF_INET, SOCK_STREAM, 0 );
     if( !(sockfd < 0) )
     {
          if( set_sockaddr_ipv4( &sa, addr, port ) < 0 )
               return -1;
          if( connect( sockfd, (struct sockaddr*) &sa, sizeof( sa ) ) < 0 )
               return -1;
     }
     return sockfd;
}


int create_listened_socket_ipv4( const char* addr, int port )
{
     struct sockaddr_in sa = { 0 };
     const int sockfd = socket( AF_INET, SOCK_STREAM, 0 );
     if( !(sockfd < 0) )
     {
          if( set_sockaddr_ipv4( &sa, addr, port ) < 0 )
               return -1;
          if( bind( sockfd, (struct sockaddr*) &sa, sizeof( sa ) ) < 0 )
               return -1;
          if( listen( sockfd, LISTENQ ) < 0 )
               return -1;
     }
     return sockfd;
}


int wrp_create_connected_socket_ipv4( const char* addr, int port )
{
     const int sockfd = create_connected_socket_ipv4( addr, port );
     if( sockfd < 0 )
          err_sys( "create_connected_socket_ipv4 error" );
     return sockfd;
}


int wrp_create_listened_socket_ipv4( const char* addr, int port )
{
     const int sockfd = create_listened_socket_ipv4( addr, port );
     if( sockfd < 0 )
          err_sys( "create_listened_socket_ipv4 error" );
     return sockfd;
}


ssize_t w_sendto( int sockfd, const void* buf, size_t len, int flags,
     const struct sockaddr* addr, socklen_t addrlen )
{
     const ssize_t nbytes = sendto( sockfd, buf, len, flags, addr, addrlen );
     if( nbytes < 0 )
          err_sys( "sendto error" );
     return nbytes;
}


ssize_t w_recvfrom( int sockfd, void* buf, size_t len, int flags,
     struct sockaddr* addr, socklen_t* addrlen )
{
     const ssize_t nbytes = recvfrom( sockfd, buf, len, flags, addr, addrlen );
     if( nbytes < 0 )
          err_sys( "recvfrom error" );
     return nbytes;
}
