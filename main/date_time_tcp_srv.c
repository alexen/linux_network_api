/*
 * date_time_tcp_srv.c
 *
 */

#include <arpa/inet.h>   /* for inet_ntop() */
#include <time.h>        /* for time() */
#include <stdio.h>       /* for snprintf() */
#include <stdlib.h>      /* for exit( EXIT_SUCCESS ) */
#include <unistd.h>      /* for getpid() */
#include <netinet/in.h>  /* for htonl() */
#include <common/const.h>
#include <tools/wrapfunc.h>


void process_request( int acpt_sock )
{
     char buff[ MAXLINE ] = { 0 };

     const time_t ct = time( 0 );
     const int nbytes = snprintf( buff, sizeof( buff ), "%.24s\r\n", ctime( &ct ) );

     wrp_write( acpt_sock, buff, nbytes );
     wrp_close( acpt_sock );

     exit( EXIT_SUCCESS );
}


int main()
{
     const char* listen_addr = "*";
     const int listen_port = 13;

     const int sockfd = wrp_create_listened_socket_ipv4( listen_addr, listen_port );

     printf( "[%d]: server started on %s:%d\n", getpid(), listen_addr, listen_port );

     while( 1 )
     {
          struct sockaddr_in cliaddr = { 0 };
          socklen_t cliaddrlen = sizeof( cliaddr );

          const int acpt_sock =
               wrp_accept( sockfd, (struct sockaddr*) &cliaddr, &cliaddrlen );

          printf( "[%d]: accepted connection from %s:%d\n", getpid(),
               inet_ntoa( cliaddr.sin_addr ), ntohs( cliaddr.sin_port ) );

          if( wrp_fork() == 0 )
          {
               /* here we are inside child process */
               wrp_close( sockfd );
               process_request( acpt_sock );
          }
          else
          {
               /* here we are inside parent process */
               wrp_close( acpt_sock );
          }
     }

     exit( EXIT_SUCCESS );
}
