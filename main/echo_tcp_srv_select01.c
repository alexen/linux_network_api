/*
 * Эхо-сервер, обрабатывающий соединения в одном потоке с помощью мультиплексирования
 */

#include <stdlib.h>
#include <common/const.h>
#include <tools/wrapfunc.h>


void process( int acptfd )
{
}


int main()
{
     const char* listenaddr = "*";
     const int listenport = SERV_PORT;

     const int listenfd = wrp_create_listened_socket_ipv4( listenaddr, listenport );

     while( 1 )
     {
          struct sockaddr_in cliaddr = { 0 };
          socklen_t cliaddrlen = sizeof( cliaddr );

          const int acptfd = wrp_accept( listenfd, (struct sockaddr*) &cliaddr, &cliaddrlen );
          process( acptfd );
     }

     exit( EXIT_SUCCESS );
}
