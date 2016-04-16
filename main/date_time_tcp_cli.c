/*
 * date_time_tcp_cli.c
 *
 * Simpliest date time TCP client
 *
 */

#include <unistd.h>           /* for read() */
#include <stdlib.h>           /* for exit( EXIT_SUCCESS ) */
#include <stdio.h>            /* for fputs() etc. */
#include <libgen.h>           /* for basename() */
#include <arpa/inet.h>        /* for inet_pton() */
#include <netinet/in.h>       /* for struct sockaddr_in */
#include <common/const.h>
#include <error/error.h>
#include <tools/wrapfunc.h>


#define DATETIME_SERVER_PORT 13

int main( int ac, char** av )
{
     if( ac != 2 )
          err_quit( "usage: %s <IP-address>", basename( av[ 0 ] ) );

     const int sockfd = wrp_create_connected_socket_ipv4( av[1], DATETIME_SERVER_PORT );

     char recvline[ MAXLINE + 1 ] = { 0 };

     while( wrp_read( sockfd, recvline, MAXLINE ) > 0 )
     {
          if( fputs( recvline, stdout ) == EOF )
               err_sys( "fputs error" );
     }

     exit( EXIT_SUCCESS );
}
