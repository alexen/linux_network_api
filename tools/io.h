/*
 * io.h
 *
 * Содержит описания функций, используемых для ввода/вывода
 *
 */

#ifndef TOOLS_IO_H_
#define TOOLS_IO_H_


ssize_t read_n( int fd, void* vptr, size_t n );
ssize_t write_n( int fd, const void* vptr, size_t n );
ssize_t readline( int fd, void* vptr, size_t maxlen );


#endif /* TOOLS_IO_H_ */
