/*
 * const.h
 *
 * Файл, содержащий набор общих констант
 *
 */

#ifndef COMMON_CONST_H_
#define COMMON_CONST_H_

#define MAXLINE     4096      /* Максимальная длина текстовой строки */
#define BUFFSIZE    8192      /* Размер буфера для чтения и записи */
#define LISTENQ     1024      /* Размер очереди соединений (второй аргумент для ф-ции listen() */
#define MAXSOCKADDR 128       /* Максимальный размер структуры sockaddr */
#define SERV_PORT   9877      /* Порт для серверов TCP и UDP */
#define MAX_FD_OPEN 1024      /* Максимальное кол-во открытых дескрипторов для процесса */

#define MIN_OF( a, b )   ((a) < (b) ? (a) : (b))
#define MAX_OF( a, b )   ((a) > (b) ? (a) : (b))

#endif /* COMMON_CONST_H_ */
