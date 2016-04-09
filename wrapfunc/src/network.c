/*
 * socket.c
 *
 */

#include <wrapfunc/wrapfunc.h>

#include <sys/socket.h>
#include <error/error.h>

int wrp_socket( int domain, int type, int protocol )
{
     const int sockfd = socket( domain, type, protocol );
     if( sockfd < 0 )
          err_sys( "socket error" );
     return sockfd;
}


void wrp_connect( int sockfd, const struct sockaddr* addr, socklen_t len )
{
     if( connect( sockfd, addr, len ) < 0 )
          err_sys( "connect error" );
}


void wrp_bind( int sockfd, const struct sockaddr* addr, socklen_t len )
{
     if( bind( sockfd, addr, len ) < 0 )
          err_sys( "bind error" );
}


void wrp_listen( int sockfd, int backlog )
{
     if( listen( sockfd, backlog ) < 0 )
          err_sys( "listen error" );
}
