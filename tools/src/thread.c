/*
 * thread.c
 *
 */

#include <errno.h>
#include <error/error.h>
#include <tools/wrapfunc.h>

void wrp_pthread_mutex_lock( pthread_mutex_t* mutex )
{
     const int n = pthread_mutex_lock( mutex );
     if( n != 0 )
     {
          errno = n;
          err_sys( "pthread_mutex_lock error" );
     }
}
