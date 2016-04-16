/*
 * Эхо-сервер, обрабатывающий соединения в одном потоке с помощью мультиплексирования
 */

#include <signal.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <common/const.h>
#include <error/error.h>
#include <tools/io.h>
#include <tools/wrapfunc.h>


/* Функционал работы с массивом дескрипторов */

#define NO_FD -1

void init_fd_array( int* fdarr, size_t fdarrlen )
{
     for( int i = 0; i < fdarrlen; ++i )
          fdarr[ i ] = NO_FD;
}


int find_free_cell_index( const int* const fdarr, size_t fdarrlen )
{
     for( int i = 0; i < fdarrlen; ++i )
          if( fdarr[ i ] == NO_FD )
               return i;
     return -1;
}


int store_fd( int* fdarr, size_t fdarrlen, int fd )
{
     const int freeidx = find_free_cell_index( fdarr, fdarrlen );
     if( freeidx < 0 )
          err_quit( "too many clients" );
     fdarr[ freeidx ] = fd;
     return freeidx;
}


void print_fd_array( const char* const prefix, int* fdarr, size_t fdarrlen )
{
     printf( "%s ", prefix );
     for( int i = 0; i < fdarrlen; ++i )
          printf( "%d ", fdarr[ i ] );
     printf( "\n" );
}


void stop_server( int sn )
{
     time_t ct = time( 0 );
     printf( "server stopped at %.24s\n", ctime( &ct ) );
     exit( EXIT_SUCCESS );
}


int main()
{
     signal( SIGINT, stop_server );

     const char* listenaddr = "*";
     const int listenport = SERV_PORT;

     const int listenfd = wrp_create_listened_socket_ipv4( listenaddr, listenport );

     printf( "server started on %s:%d\n", listenaddr, listenport );

     int client[ FD_SETSIZE ];
     init_fd_array( client, FD_SETSIZE );

     fd_set rset, allset;

     FD_ZERO( &allset );
     FD_SET( listenfd, &allset );

     int maxfd = listenfd;    /* max file descriptor */
     int maxi = -1;           /* max index for client fd array */

     while( 1 )
     {
          rset = allset;

          int nfdready = wrp_select( maxfd + 1, &rset, 0, 0, 0 );

          if( FD_ISSET( listenfd, &rset ) ) /* new client connected with us */
          {
               struct sockaddr_in cliaddr = { 0 };
               socklen_t cliaddrlen = sizeof( cliaddr );

               const int acptfd = wrp_accept( listenfd, (struct sockaddr*) &cliaddr, &cliaddrlen );

               printf( "connection accepted from %s:%d\n",
                    inet_ntoa( cliaddr.sin_addr ), ntohs( cliaddr.sin_port ) );

               /* storing fd to array */
               const int usedidx = store_fd( client, FD_SETSIZE, acptfd );
               maxi = MAX_OF( maxi, usedidx );

               /* adding fd to set */
               FD_SET( acptfd, &allset );
               maxfd = MAX_OF( maxfd, acptfd );

               if( --nfdready <= 0 )
                    continue;
          }

          for( int i = 0; i <= maxi; ++i )
          {
               const int sockfd = client[ i ];
               if( sockfd < 0 )
                    continue;
               if( FD_ISSET( sockfd, &rset ) )
               {
                    char line[ MAXLINE ] = { 0 };
                    const ssize_t n = readline( sockfd, line, MAXLINE );
                    if( n == 0 ) /* connection closed by client */
                    {
                         wrp_close( sockfd );
                         FD_CLR( sockfd, &allset );
                         client[ i ] = NO_FD;
                    }
                    else
                    {
                         write_n( sockfd, line, n );
                    }

                    if( --nfdready <= 0 )
                         break;
               }
          }
     }

     exit( EXIT_SUCCESS );
}
