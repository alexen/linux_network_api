/*
 * error.h
 *
 * Заголовочный файл с описанием интерфейса библиотеки liberror.so
 *
 */

#ifndef LINUX_NETWORK_API_ERROR_ERROR_H_
#define LINUX_NETWORK_API_ERROR_ERROR_H_


/*
 * Тип колбека для обработки ошибок
 *
 * @param file имя файла, в котором произошла ошибка
 * @param line номер строки, в которой произошла ошибка
 * @param func имя функции, в которой произошла ошибка
 * @param message сообщение об ошибке
 */
typedef void( *error_handler_t )(
     const char* file,
     int line,
     const char* func,
     const char* message
     );


#define ERROR_OCCURED_FNC_MSG( handler_name_, function_, message_ ) \
     do{ handler_name_( __FILE__, __LINE__, function_, message_ ); } while( 0 )

#define ERROR_OCCURED_MSG( handler_name_, message_ ) \
     ERROR_OCCURED_FNC_MSG( handler_name_, __FUNCTION__, message_ )


/*
 * Нефатальная ошибка, связанная с системным вызовом.
 * Выводим сообщение и возвращаем управление
 */
void err_ret( const char *fmt, ... );

/*
 * Фатальная ошибка, связанная с системным вызовом.
 * Выводим сообщение и завершаем работу.
 */
void err_sys( const char *fmt, ... );

/*
 * Фатальная ошибка, связанная с системным вызовом.
 * Выводим сообщение, сохраняем дамп памяти процесса и заканчиваем работу.
 */
void err_dump( const char *fmt, ... );

/*
 * Нефатальная ошибка, не относящаяся к системному вызову.
 * Выводим сообщение и возвращаем управление.
 */
void err_msg( const char *fmt, ... );

/*
 * Фатальная ошибка, не относящаяся к системному вызову.
 * Выводим сообщение и заканчиваем работу.
 */
void err_quit( const char *fmt, ... );


#endif /* LINUX_NETWORK_API_ERROR_ERROR_H_ */
