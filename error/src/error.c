/*
 * error.c
 *
 * Файл, содержащий обертки для обработки ошибок
 *
 */

#include <common/const.h>

#include <errno.h>  /* для errno */
#include <stdarg.h> /* заголовочный файл ANSI С */
#include <syslog.h> /* для syslog() */
#include <stdio.h>  /* для vsnprintf() */
#include <stdlib.h> /* для EXIT_FAILURE */
#include <string.h> /* для strerror() */

int daemon_proc; /* устанавливается в ненулевое значение с помощью daemon_init() */

/*
 * Выводим сообщение и возвращаем управление.
 * Вызывающий процесс задает "errnoflag" и "level".
 */
static void err_doit( int print_errno, int level, const char *fmt, va_list ap )
{
     char buf[ MAXLINE + 1 ] = { 0 };
     const int errno_save = errno;  /* значение может понадобиться вызвавшему процессу */

     vsnprintf( buf, MAXLINE, fmt, ap ); /* защищенный вариант */

     if( daemon_proc )
     {
          syslog( level, "%s: %s", buf, (print_errno ? strerror( errno_save ) : "[no errno used]") );
     }
     else
     {
          fprintf( stderr, "%s: %s\n", buf, (print_errno ? strerror( errno_save ) : "[no errno used]") );
     }
     return;
}

#define PRINT_ERRNO 1
#define NO_PRINT_ERRNO 0

void err_ret( const char *fmt, ... )
{
     va_list ap;
     va_start( ap, fmt );
     err_doit( PRINT_ERRNO, LOG_INFO, fmt, ap );
     va_end( ap );
}

void err_sys( const char *fmt, ... )
{
     va_list ap;
     va_start( ap, fmt );
     err_doit( PRINT_ERRNO, LOG_ERR, fmt, ap );
     va_end( ap );
     exit( EXIT_FAILURE );
}

void err_dump( const char *fmt, ... )
{
     va_list ap;
     va_start( ap, fmt );
     err_doit( PRINT_ERRNO, LOG_ERR, fmt, ap );
     va_end( ap );
     abort(); /* сохраняем дамп памяти и заканчиваем работу */
     exit( EXIT_FAILURE );
}

void err_msg( const char *fmt, ... )
{
     va_list ap;
     va_start( ap, fmt );
     err_doit( NO_PRINT_ERRNO, LOG_INFO, fmt, ap );
     va_end( ap );
}

void err_quit( const char *fmt, ... )
{
     va_list ap;
     va_start( ap, fmt );
     err_doit( NO_PRINT_ERRNO, LOG_ERR, fmt, ap );
     va_end( ap );
     exit( EXIT_FAILURE );
}
