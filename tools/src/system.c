/*
 * system.c
 *
 */

#include <unistd.h>
#include <error/error.h>
#include <tools/wrapfunc.h>


pid_t wrp_fork()
{
     const pid_t pid = fork();
     if( pid < 0 )
          err_sys( "fork error" );
     return pid;
}


int wrp_select( int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout )
{
     const int rc = select( nfds, readfds, writefds, exceptfds, timeout );
     if( rc < 0 )
          err_sys( "select error" );
     return rc;
}


int wrp_poll( struct pollfd* fds, nfds_t nfds, int timeout )
{
     const int nready = poll( fds, nfds, timeout );
     if( nready < 0 )
          err_sys( "poll error" );
     return nready;
}
