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
#include <wrapfunc/wrapfunc.h>


void process_request( int acpt_sock )
{
     char buff[ MAXLINE ] = { 0 };

     const time_t ct = time( 0 );
     const int nbytes = snprintf( buff, sizeof( buff ), "%.24s\r\n", ctime( &ct ) );

     printf( "[%d]: processing request with time %.24s\n", getpid(), buff );

     wrp_write( acpt_sock, buff, nbytes );
     wrp_close( acpt_sock );

     exit( EXIT_SUCCESS );
}


int main()
{
     struct sockaddr_in servaddr = { 0 };
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
     servaddr.sin_port = htons( 13 );

     const int sockfd = wrp_socket( AF_INET, SOCK_STREAM, 0 );

     wrp_bind( sockfd, (struct sockaddr*) &servaddr, sizeof( servaddr ) );
     wrp_listen( sockfd, LISTENQ );

     printf( "[%d]: server started on %s:%d\n", getpid(),
          inet_ntoa( servaddr.sin_addr ), ntohs( servaddr.sin_port ) );

     while( 1 )
     {
          struct sockaddr_in cliaddr = { 0 };
          socklen_t cliaddrlen = 0;

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
