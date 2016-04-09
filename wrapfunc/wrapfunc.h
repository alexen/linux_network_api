/*
 * wrapfunc.h
 *
 * Библиотека, содержащая функции-обертки стандартных функций.
 * Функции-обертки функционируют также, как и стандартные функции,
 * но при этом еще и обрабатывают собственные ошибки.
 *
 * Функции-обертки имеют в названии префикс wrp_
 * Например, для функции socket() аналогичная обертка будет называться wrp_socket().
 *
 */

#ifndef WRAPFUNC_WRAPFUNC_H_
#define WRAPFUNC_WRAPFUNC_H_

#include <sys/socket.h>
#include <pthread.h>


ssize_t wrp_read( int fd, void* buf, size_t count );
ssize_t wrp_write( int fd, const void* buf, size_t count );


int wrp_socket( int domain, int type, int protocol );
void wrp_connect( int sockfd, const struct sockaddr* addr, socklen_t addrlen );
void wrp_bind( int sockfd, const struct sockaddr* addr, socklen_t addrlen );
void wrp_listen( int sockfd, int backlog );
int wrp_accept( int sockfd, struct sockaddr* addr, socklen_t* addrlen );


void wrp_pthread_mutex_lock( pthread_mutex_t* mutex );


#endif /* WRAPFUNC_WRAPFUNC_H_ */
