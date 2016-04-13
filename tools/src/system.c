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
