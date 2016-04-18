/*
 * Эхо-сервер TCP, построенный на мультиплексировании с помощью ф-ции poll()
 */

#include <poll.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <error/error.h>
#include <common/const.h>
#include <tools/io.h>
#include <tools/network.h>
#include <tools/wrapfunc.h>

#define NO_FD            -1
#define NO_EVENTS        0
#define POLL_INFTIME     -1
#define OUT_OF_RANGE     -1


void pollfd_set_item( struct pollfd* item, int fd, int event )
{
     item->fd = fd;
     item->events = event;
}


void pollfd_clear_item( struct pollfd* item )
{
     item->fd = NO_FD;
     item->events = NO_EVENTS;
     item->revents = NO_EVENTS;
}


void pollfd_init_array( struct pollfd* fds, const nfds_t nfds )
{
     for( nfds_t i = 0; i < nfds; ++i )
          pollfd_clear_item( &fds[ i ] );
}


int pollfd_find_empty_cell( const struct pollfd* fds, const nfds_t nfds )
{
     for( nfds_t i = 0; i < nfds; ++i )
          if( fds[ i ].fd == NO_FD )
               return i;
     return OUT_OF_RANGE;
}


int pollfd_add_fd( struct pollfd* fds, const nfds_t nfds, int fd, int event )
{
     const int freecell =  pollfd_find_empty_cell( fds, nfds );
     if( freecell == OUT_OF_RANGE )
          err_quit( "too many clients" );
     pollfd_set_item( &fds[ freecell ], fd, event );
     return freecell;
}


int main()
{
     struct pollfd clients[ MAX_FD_OPEN ];
     pollfd_init_array( clients, MAX_FD_OPEN );

     const char* listenaddr = "*";
     const int listenport = SERV_PORT;

     const int listenfd = wrp_create_listened_socket_ipv4( listenaddr, listenport );

     printf( "server started on %s:%d\n", listenaddr, listenport );

     pollfd_set_item( &clients[ 0 ], listenfd, POLLRDNORM );

     nfds_t maxi = 0;

     while( 1 )
     {
          int nready = wrp_poll( clients, maxi + 1, POLL_INFTIME );

          if( clients[ 0 ].revents & POLLRDNORM )
          {
               struct sockaddr_in cliaddr = { 0 };
               socklen_t cliaddrlen = sizeof( cliaddr );

               const int acceptfd = wrp_accept( listenfd, (struct sockaddr*) &cliaddr, &cliaddrlen );

               printf( "connection accepted from %s:%d\n",
                    inet_ntoa( cliaddr.sin_addr ), ntohs( cliaddr.sin_port ) );

               const int i = pollfd_add_fd( clients, MAX_FD_OPEN, acceptfd, POLLRDNORM );
               maxi = MAX_OF( maxi, i );

               if( --nready <= 0 )
                    continue;
          }

          for( nfds_t i = 0; i <= maxi; ++i )
          {
               const int sockfd = clients[ i ].fd;

               if( sockfd < 0 )
                    continue;

               if( clients[ i ].revents & (POLLRDNORM | POLLERR) )
               {
                    char line[ MAXLINE ] = { 0 };
                    const int n = read( sockfd, line, MAXLINE );
                    if( n < 0 )
                    {
                         if( errno == ECONNRESET )
                         {
                              wrp_close( sockfd );
                              pollfd_clear_item( &clients[ i ] );
                         }
                         else
                         {
                              err_sys( "read error" );
                         }
                    }
                    else if( n == 0 )
                    {
                         wrp_close( sockfd );
                         pollfd_clear_item( &clients[ i ] );
                    }
                    else
                    {
                         write_n( sockfd, line, n );
                    }

                    if( --nready <= 0 )
                         break;
               }
          }
     }

     exit( EXIT_SUCCESS );
}
