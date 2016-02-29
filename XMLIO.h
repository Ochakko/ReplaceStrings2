#ifndef XMLIOFILEH
#define XMLIOFILEH

#include "XMLIOBuf.h"

enum {
	XMLIO_LOAD,
	XMLIO_WRITE,
	XMLIO_MAX
};

class CXMLIO
{
public:
	CXMLIO();
	virtual ~CXMLIO();

	int OpenXMLFile(char* filename, int srcmode);
	int Write2File(char* lpFormat, ...);
	int ReplaceSpace(char* dststr, int dstleng);

protected:
	virtual int InitParams();
	virtual int DestroyObjs();

	int WriteVoid2File( void* pvoid, unsigned int srcleng );

	int SetBuffer();

	int Read_Int( CXMLIOBuf* xmliobuf, char* startpat, char* endpat, int* dstint );
	int Read_Float( CXMLIOBuf* xmliobuf, char* startpat, char* endpat, float* dstfloat );
	int Read_Str( CXMLIOBuf* xmliobuf, char* startpat, char* endpat, char* dststr, int arrayleng );

	int GetInt( int* dstint, char* srcchar, int pos, int srcleng, int* stepnum );
	int GetFloat( float* dstfloat, char* srcchar, int pos, int srcleng, int* stepnum );
	int GetName( char* dstchar, int dstleng, char* srcchar, int pos, int srcleng );

	int SetXmlIOBuf( CXMLIOBuf* srcbuf, const char* startpat, const char* endpat, CXMLIOBuf* dstbuf, int delpatflag = 1 );

protected:
	int m_mode;
	FILE* m_file;
	//XMLIOBUF m_xmliobuf;
	CXMLIOBuf* m_xmliobuf;
	char* m_outbuf;
};

#endif
