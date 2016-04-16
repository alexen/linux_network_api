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


void input_line_v2( FILE* istream, int sockfd )
{
     char sendline[ MAXLINE ] = { 0 };
     char recvline[ MAXLINE ] = { 0 };
     fd_set rset;

     FD_ZERO( &rset );
     const int istrfd = fileno( istream );
     while( 1 )
     {
          FD_SET( istrfd, &rset );
          FD_SET( sockfd, &rset );
          const int maxfdp1 = MAX_OF( istrfd, sockfd ) + 1;

          wrp_select( maxfdp1, &rset, 0, 0, 0 );

          if( FD_ISSET( sockfd, &rset ) ) /* сокет готов на чтение */
          {
               if( readline( sockfd, recvline, MAXLINE ) == 0 )
                    err_quit( "input_line: server terminated prematurely" );
               wrp_fputs( recvline, stdout );
          }

          if( FD_ISSET( istrfd, &rset ) ) /* входной поток готов на чтение */
          {
               if( fgets( sendline, MAXLINE, istream ) == 0 )
                    return;
               write_n( sockfd, sendline, strlen( sendline ) );
          }
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
     wrp_set_sockaddr_v4( &servaddr, av[ 1 ], SERV_PORT );
     wrp_connect( sockfd, (struct sockaddr*) &servaddr, sizeof( servaddr ) );

     input_line_v2( stdin, sockfd );

     exit( EXIT_SUCCESS );
}
