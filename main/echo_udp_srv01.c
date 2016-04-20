/**
 * Эхо-сервер UDP
 */

#include <signal.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <common/const.h>
#include <tools/network.h>
#include <tools/wrapfunc.h>


void sigint_handler( int signo )
{
     time_t ct = time( 0 );
     printf( "udp echo server stopped at %.24s\n", ctime( &ct ) );
     exit( EXIT_SUCCESS );
}


int main()
{
     signal( SIGINT, sigint_handler );

     const char* const addr = "*";
     const int port = SERV_PORT;

     const int listenfd = create_bound_socket_ipv4( SOCK_DGRAM, addr, port );

     printf( "udp echo server started on %s:%d\n", addr, port );

     struct sockaddr_in cliaddr = { 0 };
     socklen_t cliaddrlen = sizeof( cliaddr );

     while( 1 )
     {
          char buf[ MAXLINE ] = { 0 };
          const ssize_t nbytes =
               w_recvfrom( listenfd, buf, MAXLINE, 0, (struct sockaddr*) &cliaddr, &cliaddrlen );

          printf( "received %ld bytes from %s:%d\n", nbytes,
               inet_ntoa( cliaddr.sin_addr ), ntohs( cliaddr.sin_port ) );

          w_sendto( listenfd, buf, nbytes, 0, (const struct sockaddr*) &cliaddr, cliaddrlen );
     }

     exit( EXIT_SUCCESS );
}
