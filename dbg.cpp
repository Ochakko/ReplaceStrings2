#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <assert.h>

#define DBGH
#include "dbg.h"

int DbgOut( const char* lpFormat, ... )
{
  if(dbgfile == NULL){
    return 0;
  }
  
  va_list Marker;
  size_t wleng;
  char outchar[7000];
  
  memset( outchar, 0, 7000 );
  
  va_start( Marker, lpFormat );
  vsnprintf( outchar, 7000, lpFormat, Marker );
  va_end( Marker );
  
  wleng = (unsigned long)strlen( outchar );
  size_t fwleng;
  fwleng = fwrite(outchar, wleng, 1, dbgfile);
  if(fwleng != wleng){
    return 1;
  }
  return 0;
  
}



int OpenDbgFile()
{
  dbgfile = NULL;

  dbgfile = fopen("dbg.txt", "w");
  if(!dbgfile){
    return 1;
  }

  DbgOut( "InitFunc: dbgfile created\r\n" );
  
  return 0;
}

int CloseDbgFile()
{
  if( dbgfile ){
		
    DbgOut( "CloseDbgFile\r\n" );
    fflush(dbgfile);
    fclose(dbgfile);
    dbgfile = NULL;
  }
  return 0;
}
