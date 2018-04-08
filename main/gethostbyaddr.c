/*
 * gethostbyaddr.c
 *
 * Created at: Apr 8, 2018
 *     Author: alexen
 */

#include <getopt.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <tools/hostent_parser.h>


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
     struct option opts[] = {
          { "v4", optional_argument, 0, '4' },
          { "v6", optional_argument, 0, '6' },
          { 0, 0, 0, 0 }
     };

     char addr[ sizeof( struct in_addr ) ];
     socklen_t addrlen = sizeof( struct in_addr );
     int family = AF_INET;

     int opt = -1;
     while( (opt = getopt_long( argc, argv, "46", opts, 0 )) != -1 )
     {
          switch( opt )
          {
               case '4':
                    family = AF_INET;
                    addrlen = sizeof( struct in_addr );
                    break;
               case '6':
                    family = AF_INET6;
                    addrlen = sizeof( struct in6_addr );
                    break;
          }
     }

     for(; optind < argc; ++optind )
     {
          inet_pton( family, argv[ optind ], addr );
          const struct hostent* hent = gethostbyaddr( addr, addrlen, family );
          if( hent == NULL )
          {
               fprintf( stderr, "error: %s: %s\n", argv[ optind ], hstrerror( h_errno ) );
               continue;
          }
          fprintf( stdout, "%s\n", argv[ optind ] );
          parse_hostent( hent, hostname_printer, alias_printer, address_printer );
     }

     return EXIT_SUCCESS;
}
