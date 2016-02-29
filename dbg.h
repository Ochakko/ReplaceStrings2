// platform sdk \ d3dim \ include ‚ÖˆÚ“®
#include <stdio.h>
#include <assert.h>
#include <string.h>

//#ifndef CallF
//#define CallF(cfunc,f) if(cfunc){ DbgOut( "file %s, line %d\r\n", __FILE__, __LINE__ ); f; }
//#endif

#ifdef DBGH
	FILE* dbgfile;

	int DbgOut( const char* lpFormat, ... );
	int OpenDbgFile();
	int CloseDbgFile();

#else
	extern FILE* dbgfile;

	extern int DbgOut( const char* lpFormat, ... );
	extern int OpenDbgFile();
	extern int CloseDbgFile();
#endif

