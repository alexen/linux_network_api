/*
 * socket.c
 *
 */

#include <wrapfunc/wrapfunc.h>

#include <sys/socket.h>
#include <error/error.h>

int wrp_socket( int domain, int type, int protocol )
{
     const int n = socket( domain, type, protocol );
     if( n < 0 )
          err_sys( "socket error" );
     return n;
}
