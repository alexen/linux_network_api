/*
 * io.c
 *
 */

#include <errno.h>
#include <unistd.h>
#include <error/error.h>
#include <tools/io.h>


ssize_t wrp_read( int fd, void* buf, size_t count )
{
     const ssize_t nbytes = read( fd, buf, count );
     if( nbytes < 0 )
          err_sys( "read error" );
     return nbytes;
}


ssize_t wrp_write( int fd, const void* buf, size_t count )
{
     const ssize_t nbytes = write( fd, buf, count );
     if( nbytes < 0 )
          err_sys( "write error" );
     return nbytes;
}


void wrp_close( int fd )
{
     if( close( fd ) < 0 )
          err_ret( "close error" );
}

ssize_t read_n( int fd, void* vptr, size_t n )
{
     char* ptr = vptr;
     size_t nleft = n;

     while( nleft > 0 )
     {
          ssize_t nread = read( fd, ptr, nleft );

          if( nread < 0 )
          {
               if( errno == EINTR )
                    nread = 0;
               else
                    return -1;
          }
          else if( nread == 0 )
               break;

          nleft -= nread;
          ptr += nread;
     }

     return n - nleft;
}


ssize_t write_n( int fd, const void* vptr, size_t n )
{
     const char* ptr = vptr;
     size_t nleft = n;

     while( nleft > 0 )
     {
          ssize_t nwritten = write( fd, ptr, nleft );

          if( nwritten <= 0 )
          {
               if( errno == EINTR )
                    nwritten = 0;
               else
                    return -1;
          }

          nleft -= nwritten;
          ptr += nwritten;
     }

     return n;
}


ssize_t readline( int fd, void* vptr, size_t maxlen )
{
     ssize_t n = 1;
     char* ptr = vptr;

     for(; n < maxlen; ++n )
     {
          char c = 0;
          const ssize_t rc = read( fd, &c, 1 );

          if( rc == 1 )
          {
               *ptr++ = c;
               if( c == '\n' )
                    break;
          }
          else if( rc == 0 )
          {
               if( n == 1 )
                    return 0;
               else
                    break;
          }
          else
          {
               if( errno == EINTR )
                    continue;

               return -1;
          }
     }

     *ptr = 0;
     return n;
}
