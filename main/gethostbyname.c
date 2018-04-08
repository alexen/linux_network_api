/*
 * tmp.c
 *
 * Created at: Apr 7, 2018
 *     Author: alexen
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>


void print( FILE* ostream, const char* title, const char* str )
{
     fprintf( ostream, "   %s: %s\n", title, (str ? str : "--") );
}


int main( int argc, char** argv )
{
     for( int i = 1; argv[i]; ++i )
     {
          const struct hostent* hent = gethostbyname( argv[ i ] );
          if( hent == NULL )
          {
               fprintf( stderr, "error: %s: %s\n", argv[ i ], hstrerror( h_errno ) );
               continue;
          }
          fprintf( stdout, "%s\n", argv[ i ] );
          print( stdout, "official name", hent->h_name );
          for( char** alias = hent->h_aliases; *alias; ++alias )
          {
               print( stdout, "alias", *alias );
          }
          char buffer[ INET6_ADDRSTRLEN ];
          for( char** addr = hent->h_addr_list; *addr; ++addr )
          {
               print(
                    stdout,
                    "address",
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
     return 0;
}
