/*
 * hostent_parser.c
 *
 * Created at: Apr 8, 2018
 *     Author: alexen
 */

#include <tools/hostent_parser.h>

#include <arpa/inet.h>
#include <netinet/in.h>


void parse_hostent(
     const struct hostent* hent,
     const hostname_handler_t on_hostname_cb,
     const alias_handler_t on_alias_cb,
     const address_handler_t on_address_cb
     )
{
     if( on_hostname_cb && hent->h_name )
     {
          on_hostname_cb( hent->h_name );
     }
     if( on_alias_cb && hent->h_aliases )
     {
          for( char** alias = hent->h_aliases; *alias; ++alias )
          {
               on_alias_cb( *alias );
          }
     }
     if( on_address_cb && hent->h_addr_list )
     {
          char buffer[ INET6_ADDRSTRLEN ];
          for( char** addr = hent->h_addr_list; *addr; ++addr )
          {
               on_address_cb(
                    inet_ntop(
                         hent->h_addrtype,
                         *addr,
                         buffer,
                         hent->h_addrtype == AF_INET
                              ? INET_ADDRSTRLEN
                              : INET6_ADDRSTRLEN
                         )
                    );
          }
     }
}
