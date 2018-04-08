/*
 * hostent_parser.h
 *
 * Created at: Apr 8, 2018
 *     Author: alexen
 */

#ifndef TOOLS_HOSTENT_PARSER_H_
#define TOOLS_HOSTENT_PARSER_H_

#include <netdb.h>

/**
 * Типы коллбеков, используемых при парсинге структуры @see struct hostent
 */
typedef void( *hostname_handler_t )( const char* hostname );
typedef void( *alias_handler_t )( const char* alias );
typedef void( *address_handler_t )( const char* address );


/**
 * Парсер структуры @see struct hostent
 *
 * При парсинге полей структуры вызываются соответствующие коллюеки
 * @note Если коллбек равен NULL, он не вызывается и соответствующая секция структуры не парсится
 *
 * @param hent указатель на структуру @see struct hostent
 * @param on_hostname_cb вызывается при парсинге struct hostent::h_name
 * @param on_alias_cb вызывается при парсинге struct hostent::h_aliases
 * @param on_address_cb вызывается при парсинге struct hostent::h_addr_list
 */
void parse_hostent(
     const struct hostent* hent,
     const hostname_handler_t on_hostname_cb,
     const alias_handler_t on_alias_cb,
     const address_handler_t on_address_cb
     );


#endif /* TOOLS_HOSTENT_PARSER_H_ */
