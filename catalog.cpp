/*  */

#include <stdio.h>    /* для printf() и т.д. */
#include <errno.h>    /* для errno */
#include <sys/types.h>/* для системных типов */
#include <dirent.h>   /* для функций каталога */
#include <string.h>   /* для функции strerror */
#include <list>
#include <string>
#include <iostream>

#include "catalog.h"
#include "default.h"


static int debug = 0;

Catalog::~Catalog() {}
int Catalog::ls() {
    process( dirc, ( char * ) "ls" );
    return 0;
}
int Catalog::ls( char * di ) {
    process( di, ( char * ) "ls" );
    return 0;
}
int Catalog::read() {
    v.clear();
    d.clear();
    process( dirc, ( char * ) "read" );
    v.remove( "." );
    v.remove( ".." );
    v.sort();
    d.sort();
    return 0;
}
void Catalog::browse() {
    std::list<std::string>::iterator pv = v.begin();
    while( pv != v.end( ) ) {
        std::cout<< *pv << " ";
        pv++;
    }
    std::cout<< std::endl;
    std::list<long>::iterator pd = d.begin();
    while( pd != d.end( ) ) {
        std::cout<< *pd << " ";
        pd++;
    }
    std::cout<< std::endl;
}
void Catalog::save() {
    d_bak.clear();
    d_bak.merge( d );
}
int Catalog::is_new() {
    std::list<long>::iterator pdb = d_bak.begin();
    std::list<long>::iterator pd = d.begin();
    while( pd != d.end() || pdb != d_bak.end() ) {
        if( *pd != *pdb ) return 1;
        pd++;
        pdb++;
    }
    LOG( "old" );
    return 0;
}
/* ---=== private ===--- */

int Catalog::process( char *dir, char *todo ) {
  char *myname = ( char * ) "process";
  DIR *dp;
  struct dirent *ent;
//  LOG( myname );

  if ( ( dp = opendir( dir ) ) == NULL )  {
  fprintf( stderr, "%s: %s: cannot open for reading: %s\n",
     myname, dir, strerror( errno ) );
  return 1;
  }

  errno = 0;
  while ( ( ent = readdir( dp ) ) != NULL ) {
    if( todo == ( char * ) "ls" )
      printf( "%8ld %s\n", ent->d_ino, ent->d_name );
    if( todo == ( char * ) "read" ){
      v.push_back( ( std::string ) ent->d_name );
      d.push_back( ent->d_ino );
    }
  }
  if ( errno != 0 ) {
    fprintf( stderr, "%s: %s: reading directory entries: %s\n",
       myname, dir, strerror( errno ) );
  return 1;
 }
 
 if ( closedir( dp ) != 0 ) {
   fprintf( stderr, "%s: %s: closedir: %s\n",
     myname, dir, strerror( errno ) );
   return 1;
 }
 
 return 0;
}

