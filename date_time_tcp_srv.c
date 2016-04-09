/*
 * date_time_tcp_srv.c
 *
 */

#include <time.h>        /* for time() */
#include <stdio.h>       /* for snprintf() */
#include <netinet/in.h>  /* for htonl() */
#include <common/const.h>
#include <wrapfunc/wrapfunc.h>


int main()
{
     struct sockaddr_in servaddr = { 0 };
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
     servaddr.sin_port = htons( 13 );

     const int sockfd = wrp_socket( AF_INET, SOCK_STREAM, 0 );

     wrp_bind( sockfd, (struct sockaddr*) &servaddr, sizeof( servaddr ) );
     wrp_listen( sockfd, LISTENQ );

     char buff[ MAXLINE ] = { 0 };

     while( 1 )
     {
          const int acpt_sock = wrp_accept( sockfd, 0, 0 );

          const time_t ct = time( 0 );
          const int nbytes = snprintf( buff, MAXLINE, "%s\r\n", ctime( &ct ) );
          wrp_write( acpt_sock, buff, nbytes );
          wrp_close( acpt_sock );
     }

     return 0;
}
