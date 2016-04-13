/*
 * Эхо-сервер TCP
 *
 */

#include <stdlib.h>
#include <netinet/in.h>
#include <tools/io.h>
#include <tools/wrapfunc.h>
#include <common/const.h>


void echo( int connect_sock )
{
     char line[ MAXLINE ] = { 0 };

     while( 1 )
     {
          const ssize_t n = readline( connect_sock, line, MAXLINE );

          if( n == 0 )
               return;

          write_n( connect_sock, line, n );
     }
}


int main()
{
     const int listen_sock = wrp_socket( AF_INET, SOCK_STREAM, 0 );

     struct sockaddr_in servaddr = { 0 };
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
     servaddr.sin_port = htons( SERV_PORT );

     wrp_bind( listen_sock, (struct sockaddr*) &servaddr, sizeof( servaddr ) );
     wrp_listen( listen_sock, LISTENQ );

     while( 1 )
     {
          struct sockaddr_in cliaddr = { 0 };
          socklen_t cliaddrlen = sizeof( cliaddr );

          const int connect_sock =
               wrp_accept( listen_sock, (struct sockaddr*) &cliaddr, &cliaddrlen );

          if( wrp_fork() == 0 )
          {
               /* child process here */
               wrp_close( listen_sock );

               echo( connect_sock );

               wrp_close( connect_sock );
               exit( EXIT_SUCCESS );
          }

          wrp_close( connect_sock );
     }

     exit( EXIT_SUCCESS );
}
