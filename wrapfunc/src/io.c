/*
 * io.c
 *
 */

#include <wrapfunc/wrapfunc.h>
#include <unistd.h>
#include <error/error.h>


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
