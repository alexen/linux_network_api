/*
 * Клиент эхо-сервера TCP
 *
 */

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <error/error.h>
#include <common/const.h>
#include <tools/io.h>
#include <tools/wrapfunc.h>


void input_line( FILE* istream, int sockfd )
{
     char sendline[ MAXLINE ] = { 0 };
     char recvline[ MAXLINE ] = { 0 };

     while( wrp_fgets( sendline, sizeof( sendline ), istream ) != 0 )
     {
          write_n( sockfd, sendline, strlen( sendline ) );

          if( readline( sockfd, recvline, sizeof( recvline ) ) == 0 )
               err_quit( "input_line: server terminated prematurely" );

          wrp_fputs( recvline, stdout );
     }
}


int main( int ac, char** av )
{
     if( ac != 2 )
     {
          err_quit( "usage: %s <IP address>\n", basename( av[ 0 ] ) );
     }

     const int sockfd = wrp_socket( AF_INET, SOCK_STREAM, 0 );

     struct sockaddr_in servaddr = { 0 };
     servaddr.sin_family = AF_INET;
     servaddr.sin_port = htons( SERV_PORT );
     wrp_inet_pton( AF_INET, av[ 1 ], &servaddr.sin_addr );

     wrp_connect( sockfd, (struct sockaddr*) &servaddr, sizeof( servaddr ) );

     input_line( stdin, sockfd );

     exit( EXIT_SUCCESS );
}
