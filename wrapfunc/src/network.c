/*
 * socket.c
 *
 */

#include <wrapfunc/wrapfunc.h>

#include <sys/socket.h>
#include <error/error.h>

int wrp_socket( int domain, int type, int protocol )
{
     const int rc = socket( domain, type, protocol );
     if( rc < 0 )
          err_sys( "socket error" );
     return rc;
}


int wrp_connect( int sockfd, const struct sockaddr* addr, socklen_t len )
{
     const int rc = connect( sockfd, addr, len );
     if( rc < 0 )
          err_sys( "connect error" );
     return rc;
}
