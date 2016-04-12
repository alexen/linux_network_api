/*
 * socket.c
 *
 */

#include <wrapfunc/wrapfunc.h>

#include <stdlib.h> /* for atoi(), getenv() */
#include <sys/socket.h>
#include <error/error.h>

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
