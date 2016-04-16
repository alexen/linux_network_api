/*
 * Эхо-сервер TCP
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <tools/io.h>
#include <tools/wrapfunc.h>
#include <common/const.h>
#include <error/error.h>


void sig_chld_handler( int signo )
{
     int stat = 0;
     pid_t pid = 0;
     while( (pid = waitpid( -1, &stat, WNOHANG )) > 0 )
          printf( "child %d terminated with status %d\n", pid, stat );
     signal( signo, sig_chld_handler );
     return;
}


void sig_int_handler( int signo )
{
     time_t ct = time( 0 );
     printf( "server stopped at %.24s\n", ctime( &ct ) );
     exit( EXIT_SUCCESS );
}


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
     signal( SIGCHLD, sig_chld_handler );
     signal( SIGINT, sig_int_handler );

     const char* listen_addr = "*";
     const int listen_port = SERV_PORT;

     const int listen_sock = wrp_create_listened_socket_ipv4( listen_addr, listen_port );

     time_t ct = time( 0 );
     printf( "server start listening on %s:%d at %.24s\n",
          listen_addr, listen_port, ctime( &ct ) );

     while( 1 )
     {
          struct sockaddr_in cliaddr = { 0 };
          socklen_t cliaddrlen = sizeof( cliaddr );

          const int connect_sock =
               accept( listen_sock, (struct sockaddr*) &cliaddr, &cliaddrlen );

          if( connect_sock < 0 )
          {
               if( errno == EINTR )
                    continue;
               else
                    err_sys( "accept error" );
          }

          printf( "connection accepted from %s:%d\n",
               inet_ntoa( cliaddr.sin_addr ), ntohs( cliaddr.sin_port ) );

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
