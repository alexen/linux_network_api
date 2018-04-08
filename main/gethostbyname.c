/*
 * tmp.c
 *
 * Created at: Apr 7, 2018
 *     Author: alexen
 */

#include <netdb.h>
#include <stdio.h>
#include <tools/hostent_parser.h>


void print( FILE* ostream, const char* title, const char* str )
{
     fprintf( ostream, "   %s: %s\n", title, (str ? str : "--") );
}


void hostname_printer( const char* str )
{
     printf( "   hostname: %s\n", str );
}


void alias_printer( const char* str )
{
     printf( "   alias: %s\n", str );
}


void address_printer( const char* str )
{
     printf( "   address: %s\n", str );
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
          parse_hostent( hent, hostname_printer, alias_printer, address_printer );
      }
     return 0;
}
