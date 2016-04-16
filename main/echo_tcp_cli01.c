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
               err_quit( "input_line: server shutdown" );

          wrp_fputs( recvline, stdout );
     }
}


void input_line_v2( FILE* istream, int sockfd )
{
     char sendline[ MAXLINE ] = { 0 };
     char recvline[ MAXLINE ] = { 0 };
     fd_set rset;

     const int istrfd = fileno( istream );
     int input_finished = 0;
     FD_ZERO( &rset );
     while( 1 )
     {
          input_finished == 0
               ? FD_SET( istrfd, &rset )
               : FD_CLR( istrfd, &rset );
          FD_SET( sockfd, &rset );

          const int maxfdp1 = MAX_OF( istrfd, sockfd ) + 1;

          wrp_select( maxfdp1, &rset, 0, 0, 0 );

          if( FD_ISSET( sockfd, &rset ) ) /* сокет готов на чтение */
          {
               if( readline( sockfd, recvline, MAXLINE ) == 0 )
               {
                    if( input_finished == 1 )
                         return; /* нормальное завершение */
                    else
                         err_quit( "input_line: server shutdown" );
               }
               wrp_fputs( recvline, stdout );
          }

          if( FD_ISSET( istrfd, &rset ) ) /* входной поток готов на чтение */
          {
               if( fgets( sendline, MAXLINE, istream ) == 0 )
               {
                    input_finished = 1;
                    shutdown( sockfd, SHUT_WR );
               }
               else
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

     const int sockfd = wrp_create_connected_socket_ipv4( av[1], SERV_PORT );

     input_line_v2( stdin, sockfd );

     exit( EXIT_SUCCESS );
}
