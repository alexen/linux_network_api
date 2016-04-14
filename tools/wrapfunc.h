/*
 * wrapfunc.h
 *
 * Содержит описание функций-оберток для стандартных функций.
 *
 * Функции-обертки функционируют также, как и стандартные функции,
 * но при этом обрабатывают и выводят на печать собственные ошибки.
 *
 * Функции-обертки содержат в названии префикс wrp_
 * Например, для функции socket() аналогичная обертка будет называться wrp_socket().
 *
 */

#ifndef TOOLS_WRAPFUNC_H_
#define TOOLS_WRAPFUNC_H_

#include <stdio.h>
#include <sys/socket.h>
#include <pthread.h>

char* wrp_fgets( char* s, int size, FILE* stream );
void wrp_fputs( const char* str, FILE* ostream );
ssize_t wrp_read( int fd, void* buf, size_t count );
ssize_t wrp_write( int fd, const void* buf, size_t count );
void wrp_close( int fd );

void wrp_inet_pton( int af, const char* src, void* dst );

int wrp_socket( int domain, int type, int protocol );
void wrp_connect( int sockfd, const struct sockaddr* addr, socklen_t addrlen );
void wrp_bind( int sockfd, const struct sockaddr* addr, socklen_t addrlen );
void wrp_listen( int sockfd, int backlog );
int wrp_accept( int sockfd, struct sockaddr* addr, socklen_t* addrlen );

pid_t wrp_fork();

void wrp_pthread_mutex_lock( pthread_mutex_t* mutex );


#endif /* TOOLS_WRAPFUNC_H_ */
