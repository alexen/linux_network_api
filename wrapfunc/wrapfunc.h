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


int wrp_socket( int domain, int type, int protocol );
void wrp_connect( int sockfd, const struct sockaddr* addr, socklen_t len );
void wrp_bind( int sockfd, const struct sockaddr* addr, socklen_t len );
void wrp_listen( int sockfd, int backlog );

void wrp_pthread_mutex_lock( pthread_mutex_t* mutex );


#endif /* WRAPFUNC_WRAPFUNC_H_ */
