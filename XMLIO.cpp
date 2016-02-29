#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <malloc.h>
#include <memory.h>
#include <string>
#include <assert.h>
#include "XMLIO.h"
#include "dbg.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "strs.h"


CXMLIO::CXMLIO()
{
  InitParams();
}

CXMLIO::~CXMLIO()
{
  DestroyObjs();
}

int CXMLIO::InitParams()
{
  m_mode = 0;
  m_xmliobuf = 0;
  m_file = NULL;
  m_outbuf = 0;

  return 0;
}

int CXMLIO::DestroyObjs()
{
  if(m_file){
    if(m_mode == XMLIO_WRITE){
      fflush(m_file);
    }
    fclose(m_file);
  }

  if(m_xmliobuf){
    delete m_xmliobuf;
    m_xmliobuf = 0;
  }

  if(m_outbuf){
    free(m_outbuf);
    m_outbuf = 0;
  }

  m_mode = 0;
  m_file = NULL;
  
  return 0;
}

int CXMLIO::WriteVoid2File( void* pvoid, unsigned int srcleng )
{
  if(!m_file){
    return 0;
  }

  size_t wsize;
  wsize = fwrite(pvoid, srcleng, 1, m_file);
  if( wsize != 1 ){
    return 1;
  }
  
  return 0;
}


int CXMLIO::Write2File( char* lpFormat, ... )
{
  int ret = -1;
  va_list Marker;
  unsigned long wleng, writeleng;

  if(!m_file){
    abort();
    return 0;
  }

  *m_outbuf = 0;
  
  va_start( Marker, lpFormat );
  ret = vsnprintf( m_outbuf, XMLIOLINELEN, lpFormat, Marker );
  va_end( Marker );
	
  if( ret < 0 ){//書き込まれた文字数
    abort();
    return 1;
  }

  if(ret >= XMLIOLINELEN){
    abort();
    return 1;
  }



  wleng = (unsigned long)strlen( m_outbuf );
  writeleng = fwrite(m_outbuf, wleng, 1, m_file); 
  if( writeleng != 1 ){
    abort();
    return 1;
  }
	
  return 0;
}

int CXMLIO::OpenXMLFile(char* filename, int srcmode)
{

  if(srcmode == 0){
    m_file = fopen(filename, "r");
  }else{
    m_file = fopen(filename, "w");
  }
  if(!m_file){
    fprintf(stderr, "file could not open error %s!!!\n", filename);
    return 1;
  }

  if(srcmode == 0){
    int res;
    res = SetBuffer();
    assert(!res);
  }else{
    m_outbuf = (char*)malloc(sizeof(char) * XMLIOLINELEN);
    if(!m_outbuf){
      abort();
      return 1;
    }
    *m_outbuf = 0;
  }

  return 0;
}

int CXMLIO::SetBuffer()
{
  int res;

  if(m_xmliobuf){
    delete m_xmliobuf;
    m_xmliobuf = 0;
  }

  struct stat stfile;
  int fileid;
  fileid = fileno(m_file);
  fstat(fileid, &stfile);
  off_t bufleng = stfile.st_size;

  m_xmliobuf = new CXMLIOBuf();
  if(!m_xmliobuf){
    abort();
    return 1;
  }
  res = m_xmliobuf->AllocBuf(bufleng);
  if(res){
    abort();
    return 1;
  }

  size_t rleng, readnum;
  rleng = bufleng;
  readnum = fread((void*)m_xmliobuf->GetBuf(), rleng, 1, m_file);
  if( readnum != 1 ){
    abort();
    return 1;
  }
  
  m_xmliobuf->SetPos(0);
  m_xmliobuf->SetIsEnd(0);

  /*
  int validleng;
  char* endptr;
  endptr = strstr( newbuf, "</XMLIO>" );
  if( endptr ){
    validleng = (int)( endptr - newbuf );
  }else{
    validleng = bufleng;
  }
  m_xmliobuf.bufleng = validleng;
  */
  
  return 0;
}


int CXMLIO::Read_Int( CXMLIOBuf* xmliobuf, char* startpat, char* endpat, int* dstint )
{
  int ret;
  char* startptr;
  startptr = strstr( xmliobuf->GetBuf() + xmliobuf->GetPos(), startpat );
  if( !startptr ){
    //		abort();
    return 1;
  }
  char* endptr;
  endptr = strstr( xmliobuf->GetBuf() + xmliobuf->GetPos(), endpat );
  if( !endptr || (endptr <= startptr) ){
    //		abort();
    return 1;
  }
  
  int endpatpos;
  endpatpos = (int)( endptr - xmliobuf->GetBuf() );
  if( (endpatpos <= 0) || (endpatpos > (int)xmliobuf->GetBufLeng()) ){
    abort();
    return 1;
  }
  
  
  char* srcchar = startptr + (int)strlen( startpat );
  int srcleng = (int)( endptr - srcchar );
  if( (srcleng <= 0) || (srcleng >= 256) ){
    abort();
    return 1;
  }


  int stepnum = 0;
  ret = GetInt( dstint, srcchar, 0, srcleng, &stepnum );
  if( ret ){
    abort();
    return 1;
  }
  
  return 0;
}
int CXMLIO::Read_Float( CXMLIOBuf* xmliobuf, char* startpat, char* endpat, float* dstfloat )
{
  int ret;
  char* startptr;
  startptr = strstr( xmliobuf->GetBuf() + xmliobuf->GetPos(), startpat );
  if( !startptr ){
    //abort();
    return 1;
  }
  char* endptr;
  endptr = strstr( xmliobuf->GetBuf() + xmliobuf->GetPos(), endpat );
  if( !endptr || (endptr <= startptr) ){
    //abort();
    return 1;
  }
  
  int endpatpos;
  endpatpos = (int)( endptr - xmliobuf->GetBuf() );
  if( (endpatpos <= 0) || (endpatpos >= (int)xmliobuf->GetBufLeng()) ){
    //abort();
    return 1;
  }
  
  char* srcchar = startptr + (int)strlen( startpat );
  int srcleng = (int)( endptr - srcchar );
  if( (srcleng <= 0) || (srcleng >= 256) ){
    //abort();
    return 1;
  }
  
  
  int stepnum = 0;
  ret = GetFloat( dstfloat, srcchar, 0, srcleng, &stepnum );
  if( ret ){
    abort();
    return 1;
  }


  return 0;
}
/*
int CXMLIO::Read_Vec3( XMLIOBUF* xmliobuf, char* startpat, char* endpat, D3DXVECTOR3* dstvec )
{
	int ret;
	char* startptr;
	startptr = strstr( xmliobuf->buf + xmliobuf->pos, startpat );
	if( !startptr ){
		abort();
		return 1;
	}
	char* endptr;
	endptr = strstr( xmliobuf->buf + xmliobuf->pos, endpat );
	if( !endptr || (endptr <= startptr) ){
		abort();
		return 1;
	}

	int endpatpos;
	endpatpos = (int)( endptr - xmliobuf->buf );
	if( (endpatpos <= 0) || (endpatpos >= (int)xmliobuf->bufleng) ){
		abort();
		return 1;
	}

	char* srcchar = startptr + (int)strlen( startpat );
	int srcleng = (int)( endptr - srcchar );
	if( (srcleng <= 0) || (srcleng >= 256) ){
		abort();
		return 1;
	}

	float xval = 0.0f;
	float yval = 0.0f;
	float zval = 0.0f;

	int srcpos = 0;
	int stepnum = 0;
	ret = GetFloat( &xval, srcchar, srcpos, srcleng, &stepnum );
	if( ret ){
		abort();
		return 1;
	}

	srcpos += stepnum;
	stepnum = 0;
	ret = GetFloat( &yval, srcchar, srcpos, srcleng, &stepnum );
	if( ret ){
		abort();
		return 1;
	}

	srcpos += stepnum;
	stepnum = 0;
	ret = GetFloat( &zval, srcchar, srcpos, srcleng, &stepnum );
	if( ret ){
		abort();
		return 1;
	}

	dstvec->x = xval;
	dstvec->y = yval;
	dstvec->z = zval;


	return 0;
}
int CXMLIO::Read_Q( XMLIOBUF* xmliobuf, char* startpat, char* endpat, CQuaternion* dstq )
{
	int ret;
	char* startptr;
	startptr = strstr( xmliobuf->buf + xmliobuf->pos, startpat );
	if( !startptr ){
		abort();
		return 1;
	}
	char* endptr;
	endptr = strstr( xmliobuf->buf + xmliobuf->pos, endpat );
	if( !endptr || (endptr <= startptr) ){
		abort();
		return 1;
	}

	int endpatpos;
	endpatpos = (int)( endptr - xmliobuf->buf );
	if( (endpatpos <= 0) || (endpatpos >= (int)xmliobuf->bufleng) ){
		abort();
		return 1;
	}

	char* srcchar = startptr + (int)strlen( startpat );
	int srcleng = (int)( endptr - srcchar );
	if( (srcleng <= 0) || (srcleng >= 256) ){
		abort();
		return 1;
	}

	float xval = 0.0f;
	float yval = 0.0f;
	float zval = 0.0f;
	float wval = 0.0f;

	int srcpos = 0;
	int stepnum = 0;
	ret = GetFloat( &xval, srcchar, srcpos, srcleng, &stepnum );
	if( ret ){
		abort();
		return 1;
	}

	srcpos += stepnum;
	stepnum = 0;
	ret = GetFloat( &yval, srcchar, srcpos, srcleng, &stepnum );
	if( ret ){
		abort();
		return 1;
	}

	srcpos += stepnum;
	stepnum = 0;
	ret = GetFloat( &zval, srcchar, srcpos, srcleng, &stepnum );
	if( ret ){
		abort();
		return 1;
	}

	srcpos += stepnum;
	stepnum = 0;
	ret = GetFloat( &wval, srcchar, srcpos, srcleng, &stepnum );
	if( ret ){
		abort();
		return 1;
	}


	dstq->x = xval;
	dstq->y = yval;
	dstq->z = zval;
	dstq->w = wval;

	return 0;
}
*/
int CXMLIO::Read_Str( CXMLIOBuf* xmliobuf, char* startpat, char* endpat, char* dststr, int arrayleng )
{
  int ret;
  char* startptr;
  startptr = strstr( xmliobuf->GetBuf() + xmliobuf->GetPos(), startpat );
  if( !startptr ){
    return 1;
  }
  char* endptr;
  endptr = strstr( xmliobuf->GetBuf() + xmliobuf->GetPos(), endpat );
  if( !endptr || (endptr <= startptr) ){
    abort();
    return 1;
  }
  
  int endpatpos;
  endpatpos = (int)( endptr - xmliobuf->GetBuf() );
  if( (endpatpos <= 0) || (endpatpos > (int)xmliobuf->GetBufLeng()) ){
    abort();
    return 1;
  }
  
  char* srcchar = startptr + (int)strlen( startpat );
  int srcleng = (int)( endptr - srcchar );
  if( (srcleng <= 0) || (srcleng >= arrayleng) ){
    abort();
    return 1;
  }
  
  ret = GetName( dststr, arrayleng, srcchar, 0, srcleng );
  if( ret ){
    abort();
    return 1;
  }
  
  return 0;
}
 
 int CXMLIO::GetInt( int* dstint, char* srcchar, int pos, int srcleng, int* stepnum )
 {
   char tempchar[256];
   memset( tempchar, 0, sizeof( char ) * 256 );
   
   int newleng = strlen(tempchar) + srcleng;
   if((newleng < 0) || (newleng >= 256)){
     abort();
     return 1;
   }
   strncpy( tempchar, srcchar + pos, srcleng );
   
   *dstint = atoi( tempchar );
   
   *stepnum = srcleng;
   
   
   return 0;
 }
 int CXMLIO::GetFloat( float* dstfloat, char* srcchar, int pos, int srcleng, int* stepnum )
 {
   char* startptr = 0;
   char* endptr = 0;
   startptr = srcchar + pos;
   int poscnt = 0;
   while( *startptr && ( (isspace( *startptr ) != 0) || (*startptr == ',') ) && (poscnt < srcleng) ){
     startptr++;
     poscnt++;
   }
   
   endptr = startptr;
   while( *endptr && ( ((*endptr >= '0') && (*endptr <= '9')) || (*endptr == '.') || (*endptr == '-')) && (poscnt < srcleng) ){
     endptr++;
     poscnt++;
   }
   char tempchar[256];
   memset( tempchar, 0, sizeof( char ) * 256 );
   
   int leng;
   leng = endptr - startptr;
   if( leng <= 0 ){
     abort();
     return 1;
   }
   
   
   int newleng = strlen(tempchar) + leng;
   if((newleng < 0) || (newleng >= 256)){
     abort();
     return 1;
   }
   strncpy( tempchar, startptr, leng );
   
   *dstfloat = (float)atof( tempchar );
   
   *stepnum = poscnt;
   
   return 0;
}
int CXMLIO::GetName( char* dstchar, int dstleng, char* srcchar, int pos, int srcleng )
{
   int newleng = strlen(dstchar) + srcleng;
   if((newleng < 0) || (newleng >= dstleng)){
     abort();
     return 1;
   }
   strncpy( dstchar, srcchar + pos, srcleng );
   *( dstchar + srcleng ) = 0;
   
   return 0;
}

int CXMLIO::SetXmlIOBuf( CXMLIOBuf* srcbuf, const char* startpat, const char* endpat, CXMLIOBuf* dstbuf, int delpatflag )
{
  char* startptr = 0;
  char* endptr = 0;
  startptr = strstr( srcbuf->GetBuf() + srcbuf->GetPos(), startpat );
  endptr = strstr( srcbuf->GetBuf() + srcbuf->GetPos(), endpat );
  
  int spatlen = (int)strlen( startpat );
  if( delpatflag && startpat ){
    startptr += spatlen;
  }
  
  if( !startptr || !endptr ){
    //		abort();
    return 1;
  }
  
  int epatlen;
  epatlen = (int)strlen( endpat );
  
  int chkendpos;
  chkendpos = (int)( endptr + epatlen - srcbuf->GetBuf() );
  if( (chkendpos >= srcbuf->GetBufLeng()) || (endptr < startptr) ){
    //		abort();
    return 1;
  }
  
  //srcのposはendpatの「終わり」の位置
  //次の切り出しはendpatを含まないようにするため
  srcbuf->SetPos(chkendpos);
  srcbuf->SetStartPos((int)(startptr - srcbuf->GetBuf()));//srcのstartposはstartpatの始めの位置

  //dstはstartpatの始めからendpatの「始め」まで
  //endpatの直前に文字列を挿入する操作などをするため
  dstbuf->SetBuf(startptr, (int)( endptr - startptr ));
  dstbuf->SetPos(0);
  dstbuf->SetStartPos(0);
  dstbuf->SetIsEnd(0);
  
  return 0;
}
 
 
int CXMLIO::ReplaceSpace(char* dststr, int dstleng)
{
  int befpos;
  int res;

  char sjspace[3];
  //little endian expression of Shift Jis Zenkaku Space
  sjspace[0] = 0x81;
  sjspace[1] = 0x40;
  sjspace[2] = 0x00;

  memset(dststr, 0, sizeof(char) * dstleng);
  
  CXMLIOBuf tdbuf;
 
  befpos = m_xmliobuf->GetPos();//前回のpos

  int ret;
  ret = SetXmlIOBuf(m_xmliobuf, "<td class", "</td>", &tdbuf);
  if (ret){
    strcpy_s(dststr, dstleng, m_xmliobuf->GetBuf() + befpos);
    fprintf(stderr, "setxmliobuf : not found : end !!!");
    return -1;
  }
  
  //tdbuf.bufまでを書き出し
  //つまりbefposからm_xmliobuf->GetStartPosの位置まで
  int firstleng = (int)(m_xmliobuf->GetStartPos() - befpos);
  strncpy_s(dststr, dstleng, m_xmliobuf->GetBuf() + m_xmliobuf->GetStartPos(), firstleng);
  
 
  //tdbufの頭から>まで
  //最初の「>」の後に<pre><code>を入れる
  char* firstgt = strstr(tdbuf.GetBuf(), ">");
  if (!firstgt){
    fprintf(stderr, "firstgt null error !!!");
    abort();
    return -1;
  }
  res = strncat_s(dststr, dstleng, tdbuf.GetBuf(), (int)(firstgt - tdbuf.GetBuf()));
  assert(!res);
  res = strcat_s(dststr, dstleng, "><pre><code>");
  assert(!res);
 
  //tdbuf内の全角スペースを半角スペース２つに置き換える。
  char convstr[XMLIOLINELEN] = { 0 };
  res = tdbuf.ConvStr(convstr, XMLIOLINELEN, (int)(firstgt + 1 - tdbuf.GetBuf()), sjspace, "  ");
  assert(!res);
  strcat_s(dststr, dstleng, convstr);
  
  //最後の</td>の代わりに</code></pre></td>を書き出し
  res = strcat_s(dststr, dstleng, "</code></pre></td>");
  assert(!res);

  return 0;
}



