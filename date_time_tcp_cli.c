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
#include <sys/socket.h>       /* for socket() */
#include <common/const.h>
#include <error/error.h>


#define DATETIME_SERVER_PORT 13

int main( int ac, char** av )
{
     if( ac != 2 )
          err_quit( "usage: %s <IP-address>", basename( av[ 0 ] ) );

     const int sockfd = socket( AF_INET, SOCK_STREAM, 0 );

     if( sockfd < 0 )
          err_sys( "socket error" );

     struct sockaddr_in servaddr = { 0 };

     servaddr.sin_family = AF_INET;
     servaddr.sin_port = htons( DATETIME_SERVER_PORT );

     if( inet_pton( AF_INET, av[ 1 ], &servaddr.sin_addr ) <= 0 )
          err_quit( "inet_pton error for %s", av[ 1 ] );

     if( connect( sockfd, (struct sockaddr*) &servaddr, sizeof( servaddr ) ) < 0 )
          err_sys( "connect error" );

     char recvline[ MAXLINE + 1 ] = { 0 };
     int n = 0;

     while( (n = read( sockfd, recvline, MAXLINE )) > 0 )
     {
          if( fputs( recvline, stdout ) == EOF )
               err_sys( "fputs error" );
     }

     if( n < 0 )
          err_sys( "read error" );

     exit( EXIT_SUCCESS );
}
