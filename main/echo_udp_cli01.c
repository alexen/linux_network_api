/**
 * Клиент для эхо-сервера UDP
 */

#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <error/error.h>
#include <common/const.h>
#include <tools/wrapfunc.h>


int main( int ac, char** av )
{
     if( ac != 2 )
          err_quit( "usage: %s <IP address>", basename( av[ 0 ] ) );

     const int sockfd = wrp_socket( AF_INET, SOCK_DGRAM, 0 );

     struct sockaddr_in servaddr = { 0 };
     const socklen_t servaddrlen = sizeof( servaddr );

     wrp_set_sockaddr_v4( &servaddr, av[ 1 ], SERV_PORT );

     char line[ MAXLINE ] = { 0 };

     while( wrp_fgets( line, MAXLINE, stdin ) != NULL )
     {
          w_sendto( sockfd, line, strlen( line ), 0, (const struct sockaddr*) &servaddr, servaddrlen );

          struct sockaddr_in replyaddr = { 0 };
          socklen_t replyaddrlen = sizeof( replyaddr );

          const ssize_t n =
               w_recvfrom( sockfd, line, MAXLINE, 0, (struct sockaddr*) &replyaddr, &replyaddrlen );

          if( servaddrlen != replyaddrlen
               || servaddr.sin_addr.s_addr != replyaddr.sin_addr.s_addr
               || servaddr.sin_port != replyaddr.sin_port )
          {
               printf( "reply from bad address (%s:%d), ignored\n",
                    inet_ntoa( replyaddr.sin_addr ), htons( replyaddr.sin_port ) );
               continue;
          }

          line[ n ] = 0;
          wrp_fputs( line, stdout );
     }

     exit( EXIT_SUCCESS );
}
