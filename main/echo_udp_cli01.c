/**
 * Клиент для эхо-сервера UDP
 */

#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <error/error.h>
#include <common/const.h>
#include <tools/wrapfunc.h>


int main( int ac, char** av )
{
     if( ac != 2 )
          err_quit( "usage: %s <IP address>", basename( av[ 0 ] ) );

     const int sockfd = wrp_socket( AF_INET, SOCK_DGRAM, 0 );

     struct sockaddr_in servaddr = { 0 };

     wrp_set_sockaddr_v4( &servaddr, av[ 1 ], SERV_PORT );

     char line[ MAXLINE ] = { 0 };

     while( wrp_fgets( line, MAXLINE, stdin ) != NULL )
     {
          socklen_t addrlen = sizeof( servaddr );
          w_sendto( sockfd, line, strlen( line ), 0, (const struct sockaddr*) &servaddr, addrlen );
          const ssize_t n =
               w_recvfrom( sockfd, line, MAXLINE, 0, (struct sockaddr*) &servaddr, &addrlen );
          line[ n ] = 0;
          wrp_fputs( line, stdout );
     }

     exit( EXIT_SUCCESS );
}
